#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <ctype.h> // สำหรับ isdigit()
#include <regex.h> // สำหรับ regular expression
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// 🏷️ Tag สำหรับ Log
static const char *TAG = "ADV_ERROR_HANDLING";

// 🚨 enum สำหรับประเภทข้อผิดพลาด
typedef enum {
    ERROR_NONE = 0,             // ไม่มีข้อผิดพลาด
    ERROR_DIVISION_BY_ZERO,     // หารด้วยศูนย์
    ERROR_INVALID_INPUT,        // ข้อมูลผิดประเภท (ตัวอย่าง: 'ABC' แทนตัวเลข)
    ERROR_OUT_OF_RANGE,         // ข้อมูลเกินขอบเขต
    ERROR_NEGATIVE_VALUE,       // ค่าติดลบไม่เหมาะสม
    ERROR_OVERFLOW,             // ข้อมูลล้น
    ERROR_UNDERFLOW,            // ข้อมูลต่ำเกินไป
    ERROR_INVALID_EMAIL_FORMAT, // รูปแบบอีเมลไม่ถูกต้อง
    ERROR_INVALID_PHONE_FORMAT, // รูปแบบเบอร์โทรศัพท์ไม่ถูกต้อง
    ERROR_INVALID_ID_FORMAT,    // รูปแบบรหัสประชาชนไม่ถูกต้อง
    ERROR_CHECKSUM_FAILED,      // Checksum ไม่ถูกต้อง
    ERROR_MAX_RETRY_ATTEMPTS,   // ลองใหม่ครบจำนวนครั้งแล้ว
} error_code_t;

// 📊 โครงสร้างผลลัพธ์
typedef struct {
    double result;
    error_code_t error;
    char message[200]; // ✅ แก้ไข: เพิ่มขนาด buffer เป็น 200
} calculation_result_t;

// 🎨 ฟังก์ชันแสดง ASCII Art ตามสถานการณ์
void show_ascii_art(error_code_t error) {
    switch(error) {
        case ERROR_NONE:
            ESP_LOGI(TAG, "   ✅ SUCCESS ✅");
            ESP_LOGI(TAG, "      🎉🎉🎉");
            ESP_LOGI(TAG, "    สำเร็จแล้ว!");
            break;
        case ERROR_DIVISION_BY_ZERO:
            ESP_LOGI(TAG, "   🍕 ÷ 0 = ❌");
            ESP_LOGI(TAG, "   😱 โอ้ะโอ!");
            ESP_LOGI(TAG, "  ไม่มีลูกค้า!");
            break;
        case ERROR_INVALID_INPUT:
            ESP_LOGI(TAG, "   📝 ABC บาท?");
            ESP_LOGI(TAG, "   🤔 งง...");
            ESP_LOGI(TAG, "  ตัวเลขหายไป");
            break;
        case ERROR_OUT_OF_RANGE:
            ESP_LOGI(TAG, "   📈 ∞∞∞∞∞");
            ESP_LOGI(TAG, "   😵 เกินขีด!");
            ESP_LOGI(TAG, "  ใหญ่เกินไป");
            break;
        case ERROR_INVALID_EMAIL_FORMAT:
            ESP_LOGI(TAG, "   📧 @mail.com");
            ESP_LOGI(TAG, "   🧐 รูปแบบผิด!");
            ESP_LOGI(TAG, "  ต้องมี @ และ .");
            break;
        case ERROR_INVALID_PHONE_FORMAT:
            ESP_LOGI(TAG, "   📞 08123456789");
            ESP_LOGI(TAG, "   🚫 เกิน 10 ตัว!");
            ESP_LOGI(TAG, "  เบอร์โทรผิด");
            break;
        case ERROR_INVALID_ID_FORMAT:
            ESP_LOGI(TAG, "   🆔 12345");
            ESP_LOGI(TAG, "   ❌ ไม่ครบ 13 หลัก!");
            ESP_LOGI(TAG, "  เลขบัตรประชาชนผิด");
            break;
        case ERROR_CHECKSUM_FAILED:
            ESP_LOGI(TAG, "   🔢 134567890123");
            ESP_LOGI(TAG, "   ⚠️ เลขไม่ตรง!");
            ESP_LOGI(TAG, "  ตรวจสอบเลขสุดท้าย");
            break;
        case ERROR_MAX_RETRY_ATTEMPTS:
            ESP_LOGI(TAG, "   🔄 ❌ ❌ ❌");
            ESP_LOGI(TAG, "   🛑 หยุดแล้ว!");
            ESP_LOGI(TAG, "  ลองใหม่ไม่สำเร็จ");
            break;
        default:
            ESP_LOGI(TAG, "   ❓ ERROR ❓");
            ESP_LOGI(TAG, "   🔧 แก้ไข");
            ESP_LOGI(TAG, "  ต้องตรวจสอบ");
    }
}

// 🛡️ ฟังก์ชันตรวจสอบการหารด้วยศูนย์
calculation_result_t safe_divide(double dividend, double divisor, const char* context) {
    calculation_result_t result = {0};
    
    ESP_LOGI(TAG, "\n🔍 ตรวจสอบการหาร: %s", context);
    ESP_LOGI(TAG, "📊 %g ÷ %g = ?", dividend, divisor);
    
    // ตรวจสอบหารด้วยศูนย์
    if (divisor == 0.0) {
        result.error = ERROR_DIVISION_BY_ZERO;
        strcpy(result.message, "❌ ข้อผิดพลาด: ไม่สามารถหารด้วยศูนย์ได้!");
        ESP_LOGE(TAG, "%s", result.message);
        show_ascii_art(ERROR_DIVISION_BY_ZERO);
        ESP_LOGI(TAG, "💡 แนะนำ: ตรวจสอบจำนวนลูกค้าก่อนแบ่งพิซซ่า");
        return result;
    }
    
    // ตรวจสอบผลลัพธ์ล้น
    result.result = dividend / divisor;
    if (isinf(result.result)) {
        result.error = ERROR_OVERFLOW;
        strcpy(result.message, "⚠️ เตือน: ผลลัพธ์เป็น infinity!");
        ESP_LOGW(TAG, "%s", result.message);
        return result;
    }
    
    // สำเร็จ
    result.error = ERROR_NONE;
    sprintf(result.message, "✅ สำเร็จ: %.2f ÷ %.2f = %.2f", dividend, divisor, result.result);
    ESP_LOGI(TAG, "%s", result.message);
    show_ascii_art(ERROR_NONE);
    
    return result;
}

// 💰 ฟังก์ชันตรวจสอบค่าเงิน
calculation_result_t validate_money(double amount, const char* description) {
    calculation_result_t result = {0};
    
    ESP_LOGI(TAG, "\n💰 ตรวจสอบเงิน: %s", description);
    ESP_LOGI(TAG, "💵 จำนวน: %.2f บาท", amount);
    
    // ตรวจสอบค่าติดลบ
    if (amount < 0) {
        result.error = ERROR_NEGATIVE_VALUE;
        strcpy(result.message, "❌ ข้อผิดพลาด: จำนวนเงินไม่สามารถติดลบได้!");
        ESP_LOGE(TAG, "%s", result.message);
        ESP_LOGI(TAG, "💡 แนะนำ: ตรวจสอบการคิดเงินใหม่");
        return result;
    }
    
    // ตรวจสอบเกินขีดจำกัด (1 ล้านล้าน)
    if (amount > 1000000000000.0) {
        result.error = ERROR_OUT_OF_RANGE;
        strcpy(result.message, "⚠️ เตือน: จำนวนเงินเกินขีดจำกัดระบบ!");
        ESP_LOGW(TAG, "%s", result.message);
        show_ascii_art(ERROR_OUT_OF_RANGE);
        ESP_LOGI(TAG, "💡 แนะนำ: ใช้ระบบธนาคารกลาง");
        return result;
    }
    
    // ตรวจสอบทศนิยมมากเกินไป
    double rounded = round(amount * 100) / 100;  // ปัดเศษสตางค์
    if (fabs(amount - rounded) > 0.001) {
        ESP_LOGW(TAG, "⚠️ เตือน: ปัดเศษจาก %.4f เป็น %.2f บาท", amount, rounded);
        amount = rounded;
    }
    
    result.result = amount;
    result.error = ERROR_NONE;
    sprintf(result.message, "✅ จำนวนเงินถูกต้อง: %.2f บาท", amount);
    ESP_LOGI(TAG, "%s", result.message);
    
    return result;
}

// 🔢 ฟังก์ชันตรวจสอบข้อมูลตัวเลข
calculation_result_t validate_number(const char* input, const char* field_name) {
    calculation_result_t result = {0};
    
    ESP_LOGI(TAG, "\n🔢 ตรวจสอบตัวเลข: %s", field_name);
    ESP_LOGI(TAG, "📝 ข้อมูลที่ป้อน: '%s'", input);
    
    // ตรวจสอบ NULL หรือ empty
    if (input == NULL || strlen(input) == 0) {
        result.error = ERROR_INVALID_INPUT;
        strcpy(result.message, "❌ ข้อผิดพลาด: ไม่มีข้อมูล!");
        ESP_LOGE(TAG, "%s", result.message);
        return result;
    }
    
    // ลองแปลงเป็นตัวเลข
    char* endptr;
    double value = strtod(input, &endptr);
    
    // ตรวจสอบว่าแปลงได้ทั้งหมดหรือไม่
    if (*endptr != '\0') {
        result.error = ERROR_INVALID_INPUT;
        sprintf(result.message, "❌ ข้อผิดพลาด: '%s' ไม่ใช่ตัวเลข!", input);
        ESP_LOGE(TAG, "%s", result.message);
        show_ascii_art(ERROR_INVALID_INPUT);
        ESP_LOGI(TAG, "💡 แนะนำ: ใช้เฉพาะตัวเลข 0-9 และจุดทศนิยม");
        return result;
    }
    
    // ตรวจสอบ NaN หรือ infinite
    if (isnan(value) || isinf(value)) {
        result.error = ERROR_INVALID_INPUT;
        strcpy(result.message, "❌ ข้อผิดพลาด: ตัวเลขไม่ถูกต้อง!");
        ESP_LOGE(TAG, "%s", result.message);
        return result;
    }
    
    result.result = value;
    result.error = ERROR_NONE;
    sprintf(result.message, "✅ ตัวเลขถูกต้อง: %.2f", value);
    ESP_LOGI(TAG, "%s", result.message);
    
    return result;
}

// 📊 ฟังก์ชันคำนวณดอกเบี้ยอย่างปลอดภัย
calculation_result_t calculate_interest(double principal, double rate, int years) {
    calculation_result_t result = {0};
    
    ESP_LOGI(TAG, "\n🏦 คำนวณดอกเบี้ย");
    ESP_LOGI(TAG, "💰 เงินต้น: %.2f บาท", principal);
    ESP_LOGI(TAG, "📈 อัตราดอกเบี้ย: %.2f%% ต่อปี", rate);
    ESP_LOGI(TAG, "⏰ ระยะเวลา: %d ปี", years);
    
    // ตรวจสอบเงินต้น
    if (principal <= 0) {
        result.error = ERROR_NEGATIVE_VALUE;
        strcpy(result.message, "❌ เงินต้นต้องมากกว่าศูนย์!");
        ESP_LOGE(TAG, "%s", result.message);
        return result;
    }
    
    // ตรวจสอบอัตราดอกเบี้ย
    if (rate < -100 || rate > 100) {
        result.error = ERROR_OUT_OF_RANGE;
        strcpy(result.message, "❌ อัตราดอกเบี้ยไม่สมเหตุสมผล!");
        ESP_LOGE(TAG, "%s", result.message);
        ESP_LOGI(TAG, "💡 แนะนำ: ใช้อัตรา -100% ถึง 100%");
        return result;
    }
    
    // ตรวจสอบระยะเวลา
    if (years < 0 || years > 100) {
        result.error = ERROR_OUT_OF_RANGE;
        strcpy(result.message, "❌ ระยะเวลาไม่สมเหตุสมผล!");
        ESP_LOGE(TAG, "%s", result.message);
        return result;
    }
    
    // คำนวณดอกเบี้ยแบบง่าย
    double interest = principal * (rate / 100.0) * years;
    double total = principal + interest;
    
    // ตรวจสอบ overflow
    if (total > DBL_MAX / 2) {
        result.error = ERROR_OVERFLOW;
        strcpy(result.message, "⚠️ เตือน: ผลลัพธ์ใหญ่เกินไป!");
        ESP_LOGW(TAG, "%s", result.message);
        return result;
    }
    
    result.result = total;
    result.error = ERROR_NONE;
    sprintf(result.message, "✅ ดอกเบี้ย: %.2f บาท, รวม: %.2f บาท", interest, total);
    ESP_LOGI(TAG, "%s", result.message);
    
    return result;
}

// 1. ตรวจสอบอีเมล (ใช้ Regular Expression)
calculation_result_t validate_email(const char* email) {
    calculation_result_t result = {0};
    regex_t regex;
    int ret;
    
    ESP_LOGI(TAG, "\n📧 ตรวจสอบอีเมล: '%s'", email);

    // รูปแบบ regex สำหรับอีเมล
    const char *pattern = "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";

    ret = regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE);
    if (ret) {
        ESP_LOGE(TAG, "❌ ข้อผิดพลาด: ไม่สามารถคอมไพล์ regex ได้!");
        result.error = ERROR_INVALID_INPUT;
        strcpy(result.message, "❌ ข้อผิดพลาดภายใน: ไม่สามารถตรวจสอบรูปแบบได้");
        return result;
    }
    
    ret = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) { // Match
        result.error = ERROR_NONE;
        strcpy(result.message, "✅ รูปแบบอีเมลถูกต้อง");
        ESP_LOGI(TAG, "%s", result.message);
        show_ascii_art(ERROR_NONE);
    } else if (ret == REG_NOMATCH) { // No match
        result.error = ERROR_INVALID_EMAIL_FORMAT;
        strcpy(result.message, "❌ ข้อผิดพลาด: รูปแบบอีเมลไม่ถูกต้อง!");
        ESP_LOGE(TAG, "%s", result.message);
        show_ascii_art(ERROR_INVALID_EMAIL_FORMAT);
        ESP_LOGI(TAG, "💡 แนะนำ: ต้องมีชื่อผู้ใช้, เครื่องหมาย '@', ชื่อโดเมน และ '.com'/.co.th' เป็นต้น");
    } else { // Other errors
        result.error = ERROR_INVALID_INPUT;
        strcpy(result.message, "❌ ข้อผิดพลาด: การตรวจสอบล้มเหลว");
        ESP_LOGE(TAG, "%s", result.message);
    }

    return result;
}

// 2. ตรวจสอบเบอร์โทรศัพท์ (ใช้ Checksum)
calculation_result_t validate_phone_number(const char* phone) {
    calculation_result_t result = {0};
    int len = strlen(phone);
    int sum_digits = 0;
    
    ESP_LOGI(TAG, "\n📞 ตรวจสอบเบอร์โทรศัพท์: '%s'", phone);

    if (len != 10) {
        result.error = ERROR_INVALID_PHONE_FORMAT;
        strcpy(result.message, "❌ ข้อผิดพลาด: เบอร์โทรศัพท์ต้องมี 10 หลัก!");
        ESP_LOGE(TAG, "%s", result.message);
        show_ascii_art(ERROR_INVALID_PHONE_FORMAT);
        ESP_LOGI(TAG, "💡 แนะนำ: ตัวอย่าง 0811234567");
        return result;
    }

    for (int i = 0; i < len; i++) {
        // ✅ แก้ไข: เพิ่ม (unsigned char)
        if (!isdigit((unsigned char)phone[i])) { 
            result.error = ERROR_INVALID_PHONE_FORMAT;
            strcpy(result.message, "❌ ข้อผิดพลาด: เบอร์โทรศัพท์ต้องเป็นตัวเลขเท่านั้น!");
            ESP_LOGE(TAG, "%s", result.message);
            show_ascii_art(ERROR_INVALID_PHONE_FORMAT);
            ESP_LOGI(TAG, "💡 แนะนำ: ตัวอย่าง 0811234567");
            return result;
        }
        sum_digits += phone[i] - '0';
    }

    if (sum_digits % 10 != 0) {
        ESP_LOGW(TAG, "⚠️ เตือน: Checksum ไม่ตรง!");
    }

    result.error = ERROR_NONE;
    strcpy(result.message, "✅ รูปแบบเบอร์โทรศัพท์ถูกต้อง");
    ESP_LOGI(TAG, "%s", result.message);
    show_ascii_art(ERROR_NONE);

    return result;
}

// 3. ตรวจสอบรหัสประจำตัวประชาชน (ใช้ Checksum)
int calculate_id_checksum(const char* id) {
    int sum = 0;
    for (int i = 0; i < 12; i++) {
        int digit = id[i] - '0';
        sum += digit * (13 - i);
    }
    return (11 - (sum % 11)) % 10;
}

calculation_result_t validate_thai_id(const char* id) {
    calculation_result_t result = {0};
    int len = strlen(id);
    
    ESP_LOGI(TAG, "\n🆔 ตรวจสอบรหัสประจำตัวประชาชน: '%s'", id);

    if (len != 13) {
        result.error = ERROR_INVALID_ID_FORMAT;
        strcpy(result.message, "❌ ข้อผิดพลาด: รหัสประชาชนต้องมี 13 หลัก!");
        ESP_LOGE(TAG, "%s", result.message);
        show_ascii_art(ERROR_INVALID_ID_FORMAT);
        return result;
    }

    for (int i = 0; i < len; i++) {
        // ✅ แก้ไข: เพิ่ม (unsigned char)
        if (!isdigit((unsigned char)id[i])) {
            result.error = ERROR_INVALID_ID_FORMAT;
            strcpy(result.message, "❌ ข้อผิดพลาด: รหัสประชาชนต้องเป็นตัวเลขเท่านั้น!");
            ESP_LOGE(TAG, "%s", result.message);
            show_ascii_art(ERROR_INVALID_ID_FORMAT);
            return result;
        }
    }
    
    int expected_checksum = calculate_id_checksum(id);
    int actual_checksum = id[12] - '0';

    if (expected_checksum != actual_checksum) {
        result.error = ERROR_CHECKSUM_FAILED;
        strcpy(result.message, "❌ ข้อผิดพลาด: Checksum รหัสประชาชนไม่ถูกต้อง!");
        ESP_LOGE(TAG, "%s", result.message);
        show_ascii_art(ERROR_CHECKSUM_FAILED);
        ESP_LOGI(TAG, "💡 แนะนำ: เลขหลักที่ 13 ควรเป็น %d", expected_checksum);
        return result;
    }

    result.error = ERROR_NONE;
    strcpy(result.message, "✅ รูปแบบรหัสประชาชนถูกต้องและ Checksum ผ่าน");
    ESP_LOGI(TAG, "%s", result.message);
    show_ascii_art(ERROR_NONE);

    return result;
}

// 4. สร้างระบบ Retry Mechanism
typedef calculation_result_t (*operation_func)(void*);

// โครงสร้างสำหรับข้อมูลที่ต้องส่งให้ operation
typedef struct {
    double dividend;
    double divisor;
    const char* context;
} safe_divide_params_t;

// ฟังก์ชันห่อหุ้ม safe_divide เพื่อให้เข้ากับ operation_func
calculation_result_t safe_divide_wrapper(void* param) {
    safe_divide_params_t* p = (safe_divide_params_t*)param;
    return safe_divide(p->dividend, p->divisor, p->context);
}

calculation_result_t retry_mechanism(operation_func op, void* param, int max_retries, TickType_t delay_ms) {
    calculation_result_t result = {0};
    int retry_count = 0;

    while (retry_count <= max_retries) {
        ESP_LOGI(TAG, "🔄 กำลังลองครั้งที่ %d/%d...", retry_count + 1, max_retries + 1);
        result = op(param);

        if (result.error == ERROR_NONE) {
            ESP_LOGI(TAG, "✅ สำเร็จในการลองครั้งที่ %d", retry_count + 1);
            return result;
        }
        
        if (result.error == ERROR_DIVISION_BY_ZERO || result.error == ERROR_INVALID_INPUT) {
            ESP_LOGE(TAG, "❌ ข้อผิดพลาดร้ายแรง: หยุดการลองใหม่");
            show_ascii_art(result.error);
            return result;
        }

        vTaskDelay(pdMS_TO_TICKS(delay_ms));
        retry_count++;
    }

    result.error = ERROR_MAX_RETRY_ATTEMPTS;
    strcpy(result.message, "❌ ข้อผิดพลาด: ลองใหม่ไม่สำเร็จ!");
    ESP_LOGE(TAG, "%s", result.message);
    show_ascii_art(ERROR_MAX_RETRY_ATTEMPTS);
    return result;
}

// 🍕 ฟังก์ชันจำลองสถานการณ์ร้านพิซซ่า
void pizza_shop_scenario(void) {
    ESP_LOGI(TAG, "\n🍕 === สถานการณ์ร้านพิซซ่า ===");
    ESP_LOGI(TAG, "📖 วันนี้ฝนตก ไม่มีลูกค้ามากิน");
    
    calculation_result_t result;
    
    result = safe_divide(12, 4, "แบ่งพิซซ่า 12 ชิ้นให้ลูกค้า 4 คน");
    if (result.error != ERROR_NONE) {
        ESP_LOGE(TAG, "การดำเนินการล้มเหลว: %s", result.message);
    }
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    result = safe_divide(12, 0, "แบ่งพิซซ่า 12 ชิ้นให้ลูกค้า 0 คน");
    if (result.error != ERROR_NONE) {
        ESP_LOGE(TAG, "การดำเนินการล้มเหลว: %s", result.message);
    }
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    ESP_LOGI(TAG, "\n🌞 ฝนหยุดแล้ว! มีลูกค้ามา 3 คน");
    result = safe_divide(12, 3, "แบ่งพิซซ่า 12 ชิ้นให้ลูกค้า 3 คน");
    if (result.error != ERROR_NONE) {
        ESP_LOGE(TAG, "การดำเนินการล้มเหลว: %s", result.message);
    }
}

// 💰 ฟังก์ชันจำลองสถานการณ์ร้านขายของ
void shop_scenario(void) {
    ESP_LOGI(TAG, "\n🛒 === สถานการณ์ร้านขายของ ===");
    ESP_LOGI(TAG, "📖 เจ้าของร้านป้อนข้อมูลผิด");
    
    calculation_result_t result;
    
    result = validate_number("ABC", "ราคาสินค้า");
    if (result.error != ERROR_NONE) {
        ESP_LOGE(TAG, "การดำเนินการล้มเหลว: %s", result.message);
    }
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    result = validate_number("12.50", "ราคาสินค้า");
    if (result.error != ERROR_NONE) {
        ESP_LOGE(TAG, "การดำเนินการล้มเหลว: %s", result.message);
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
    
    result = validate_money(-50.0, "เงินทอน");
    if (result.error != ERROR_NONE) {
        ESP_LOGE(TAG, "การดำเนินการล้มเหลว: %s", result.message);
    }
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    result = validate_money(25.75, "เงินทอน");
    if (result.error != ERROR_NONE) {
        ESP_LOGE(TAG, "การดำเนินการล้มเหลว: %s", result.message);
    }
}

// 🏦 ฟังก์ชันจำลองสถานการณ์ธนาคาร
void bank_scenario(void) {
    ESP_LOGI(TAG, "\n🏦 === สถานการณ์ธนาคาร ===");
    ESP_LOGI(TAG, "📖 ลูกค้าฝากเงินและคำนวณดอกเบี้ย");
    
    calculation_result_t result;
    
    result = calculate_interest(100000, 2.5, 5);
    if (result.error != ERROR_NONE) {
        ESP_LOGE(TAG, "การดำเนินการล้มเหลว: %s", result.message);
    }
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    result = calculate_interest(100000, -5.0, 5);
    if (result.error != ERROR_NONE) {
        ESP_LOGE(TAG, "การดำเนินการล้มเหลว: %s", result.message);
    }
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    result = validate_money(999999999999.0, "เงินฝาก");
    if (result.error != ERROR_NONE) {
        ESP_LOGE(TAG, "การดำเนินการล้มเหลว: %s", result.message);
    }
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    result = calculate_interest(100000, 3.0, 10);
    if (result.error != ERROR_NONE) {
        ESP_LOGE(TAG, "การดำเนินการล้มเหลว: %s", result.message);
    }
}

// 🌐 ฟังก์ชันจำลองสถานการณ์การป้อนข้อมูล
void user_input_scenario(void) {
    ESP_LOGI(TAG, "\n📝 === สถานการณ์การป้อนข้อมูล ===");
    calculation_result_t result;
    
    result = validate_email("test@example.com");
    if (result.error != ERROR_NONE) { ESP_LOGE(TAG, "การตรวจสอบล้มเหลว: %s", result.message); }
    vTaskDelay(pdMS_TO_TICKS(1000));
    result = validate_email("test@examplecom");
    if (result.error != ERROR_NONE) { ESP_LOGE(TAG, "การตรวจสอบล้มเหลว: %s", result.message); }
    vTaskDelay(pdMS_TO_TICKS(1000));
    result = validate_email("invalid-email");
    if (result.error != ERROR_NONE) { ESP_LOGE(TAG, "การตรวจสอบล้มเหลว: %s", result.message); }
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    result = validate_phone_number("0812345678");
    if (result.error != ERROR_NONE) { ESP_LOGE(TAG, "การตรวจสอบล้มเหลว: %s", result.message); }
    vTaskDelay(pdMS_TO_TICKS(1000));
    result = validate_phone_number("081234567");
    if (result.error != ERROR_NONE) { ESP_LOGE(TAG, "การตรวจสอบล้มเหลว: %s", result.message); }
    vTaskDelay(pdMS_TO_TICKS(1000));
    result = validate_phone_number("081234567A");
    if (result.error != ERROR_NONE) { ESP_LOGE(TAG, "การตรวจสอบล้มเหลว: %s", result.message); }
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    result = validate_thai_id("1101234567890");
    if (result.error != ERROR_NONE) { ESP_LOGE(TAG, "การตรวจสอบล้มเหลว: %s", result.message); }
    vTaskDelay(pdMS_TO_TICKS(1000));
    result = validate_thai_id("1101234567891");
    if (result.error != ERROR_NONE) { ESP_LOGE(TAG, "การตรวจสอบล้มเหลว: %s", result.message); }
    vTaskDelay(pdMS_TO_TICKS(2000));
    result = validate_thai_id("110123456789");
    if (result.error != ERROR_NONE) { ESP_LOGE(TAG, "การตรวจสอบล้มเหลว: %s", result.message); }
}

// 🔄 ฟังก์ชันจำลองระบบ Retry
void retry_scenario(void) {
    ESP_LOGI(TAG, "\n🔄 === สถานการณ์ Retry Mechanism ===");
    
    safe_divide_params_t params_success = { .dividend = 10.0, .divisor = 2.0, .context = "แบ่ง 10/2" };
    safe_divide_params_t params_fail = { .dividend = 10.0, .divisor = 0.0, .context = "แบ่ง 10/0" };

    ESP_LOGI(TAG, "📖 ทดสอบการ Retry ที่สำเร็จตั้งแต่ครั้งแรก");
    retry_mechanism(safe_divide_wrapper, &params_success, 3, 1000);
    vTaskDelay(pdMS_TO_TICKS(3000));
    
    ESP_LOGI(TAG, "📖 ทดสอบการ Retry ที่จะล้มเหลวเสมอ");
    retry_mechanism(safe_divide_wrapper, &params_fail, 3, 1000);
    vTaskDelay(pdMS_TO_TICKS(3000));
    
    ESP_LOGI(TAG, "📖 ลองจินตนาการว่ามีฟังก์ชันที่อาจจะล้มเหลวชั่วคราว เช่น การเชื่อมต่อเครือข่าย");
    ESP_LOGI(TAG, "💡 ในสถานการณ์จริง retry mechanism เหมาะกับข้อผิดพลาดที่แก้ไขได้เองในภายหลัง");
}

// 📊 ฟังก์ชันสรุปความรู้
void show_error_handling_summary(void) {
    ESP_LOGI(TAG, "\n📚 === สรุปการจัดการข้อผิดพลาดขั้นสูง ===");
    ESP_LOGI(TAG, "╔════════════════════════════════════════════════╗");
    ESP_LOGI(TAG, "║              ประเภทข้อผิดพลาดเพิ่มเติม          ║");
    ESP_LOGI(TAG, "╠════════════════════════════════════════════════╣");
    ESP_LOGI(TAG, "║ 📧 Invalid Email Format - รูปแบบอีเมลผิด     ║");
    ESP_LOGI(TAG, "║ 📞 Invalid Phone Format - รูปแบบเบอร์โทรศัพท์ผิด ║");
    ESP_LOGI(TAG, "║ 🆔 Invalid ID Format - รหัสประชาชนผิด         ║");
    ESP_LOGI(TAG, "║ 🔢 Checksum Failed - เลขตรวจสอบไม่ตรง         ║");
    ESP_LOGI(TAG, "║ 🔄 Max Retry Attempts - ลองใหม่เกินจำนวนครั้ง ║");
    ESP_LOGI(TAG, "╚════════════════════════════════════════════════╝");
    
    ESP_LOGI(TAG, "\n🛡️ === หลักการจัดการข้อผิดพลาดเพิ่มเติม ===");
    ESP_LOGI(TAG, "✅ 1. ใช้ Regular Expression สำหรับรูปแบบที่ซับซ้อน");
    ESP_LOGI(TAG, "✅ 2. ใช้ Checksum หรือการคำนวณเพื่อยืนยันความถูกต้องของข้อมูล");
    ESP_LOGI(TAG, "✅ 3. สร้างระบบ Retry Mechanism สำหรับข้อผิดพลาดชั่วคราว");
    ESP_LOGI(TAG, "✅ 4. แยกประเภทข้อผิดพลาดให้ชัดเจนและให้ข้อมูลที่เป็นประโยชน์");
}

void app_main(void) {
    ESP_LOGI(TAG, "🚀 เริ่มต้นโปรแกรมจัดการข้อผิดพลาดขั้นสูง!");
    ESP_LOGI(TAG, "🛡️ การตรวจสอบและป้องกันข้อผิดพลาดที่ซับซ้อน\n");
    
    vTaskDelay(pdMS_TO_TICKS(1000));
    
    pizza_shop_scenario();
    vTaskDelay(pdMS_TO_TICKS(3000));
    
    shop_scenario();
    vTaskDelay(pdMS_TO_TICKS(3000));
    
    bank_scenario();
    vTaskDelay(pdMS_TO_TICKS(3000));
    
    user_input_scenario();
    vTaskDelay(pdMS_TO_TICKS(3000));
    
    retry_scenario();
    vTaskDelay(pdMS_TO_TICKS(3000));
    
    show_error_handling_summary();
    
    ESP_LOGI(TAG, "\n✅ เสร็จสิ้นการเรียนรู้การจัดการข้อผิดพลาด!");
    ESP_LOGI(TAG, "🎓 ได้เรียนรู้: enum, struct, error codes, และการตรวจสอบข้อมูลขั้นสูง");
    ESP_LOGI(TAG, "🏆 ตอนนี้คุณสามารถเขียนโค้ดที่ปลอดภัยและน่าเชื่อถือมากขึ้นแล้ว!");
}