#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "SHOPPING_MATH";

// โครงสร้างข้อมูลสินค้า
typedef struct {
    char name[50];          // ชื่อสินค้า
    int quantity;           // จำนวน
    float price_per_unit;   // ราคาต่อหน่วย
    float total_price;      // ราคารวม
} product_t;

// ฟังก์ชันคำนวณราคาสินค้า
void calculate_product_total(product_t *product) {
    product->total_price = product->quantity * product->price_per_unit;
}

// ฟังก์ชันแสดงรายการสินค้า
void display_product(const product_t *product) {
    ESP_LOGI(TAG, "   %s: %d × %.2f = %.2f บาท", 
             product->name, product->quantity, product->price_per_unit, product->total_price);
}

// ฟังก์ชันคำนวณราคารวมทั้งหมด
float calculate_total_bill(product_t products[], int count) {
    float total = 0.0;
    for (int i = 0; i < count; i++) {
        calculate_product_total(&products[i]);
        total += products[i].total_price;
    }
    return total;
}

// ฟังก์ชันใช้ส่วนลด (เปอร์เซ็นต์)
float apply_discount_percent(float total, float percent) {
    return total - (total * percent / 100.0);
}

// ฟังก์ชันบวก VAT
float apply_vat(float total, float vat_percent) {
    return total + (total * vat_percent / 100.0);
}

// ฟังก์ชันแบ่งจ่าย
float split_payment(float amount, int people) {
    if (people <= 0) {
        ESP_LOGE(TAG, "Error: จำนวนคนต้องมากกว่า 0");
        return 0.0;
    }
    return amount / people;
}

void app_main(void)
{
    ESP_LOGI(TAG, "🛒 เริ่มต้นโปรแกรมซื้อของที่ตลาด 🛒");
    ESP_LOGI(TAG, "=====================================");
    
    // ข้อมูลการซื้อของ
    product_t products[] = {
        {"แอปเปิ้ล", 6, 15.0, 0.0},
        {"กล้วย", 12, 8.0, 0.0},
        {"ส้ม", 8, 12.0, 0.0},
        {"กาแฟ", 2, 45.0, 0.0}  // ✅ เพิ่มสินค้าที่ชอบ
    };
    int product_count = sizeof(products) / sizeof(products[0]);
    
    float discount_percent = 10.0;   // ✅ ส่วนลดเปอร์เซ็นต์
    float vat_percent = 7.0;         // ✅ VAT 7%
    int people = 3;                  // จำนวนคนที่จะแบ่งจ่าย
    
    // แสดงโจทย์
    ESP_LOGI(TAG, "📖 โจทย์:");
    ESP_LOGI(TAG, "   แม่ไปซื้อของที่ตลาด:");
    for (int i = 0; i < product_count; i++) {
        ESP_LOGI(TAG, "   - %s: %d หน่วย หน่วยละ %.2f บาท", 
                 products[i].name, products[i].quantity, products[i].price_per_unit);
    }
    ESP_LOGI(TAG, "   - ส่วนลด: %.0f%%", discount_percent);
    ESP_LOGI(TAG, "   - ภาษี VAT: %.0f%%", vat_percent);
    ESP_LOGI(TAG, "   - แบ่งจ่าย: %d คน", people);
    ESP_LOGI(TAG, "");
    
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    
    // คำนวณราคารวมแต่ละสินค้า
    ESP_LOGI(TAG, "🧮 ขั้นตอนการคิด:");
    ESP_LOGI(TAG, "   1. คำนวณราคาแต่ละสินค้า (การคูณ):");
    
    float subtotal = calculate_total_bill(products, product_count);
    
    for (int i = 0; i < product_count; i++) {
        display_product(&products[i]);
    }
    ESP_LOGI(TAG, "");
    
    // รวมราคาทั้งหมด
    ESP_LOGI(TAG, "   2. รวมราคาทั้งหมด (การบวก): %.2f บาท", subtotal);
    
    // หักส่วนลด
    float discounted_total = apply_discount_percent(subtotal, discount_percent);
    ESP_LOGI(TAG, "   3. หักส่วนลด %.0f%% (การลบ): %.2f บาท", discount_percent, discounted_total);
    
    // คำนวณภาษี VAT
    float total_with_vat = apply_vat(discounted_total, vat_percent);
    ESP_LOGI(TAG, "   4. บวก VAT %.0f%% (การบวก): %.2f บาท", vat_percent, total_with_vat);
    
    // แบ่งจ่าย
    float per_person = split_payment(total_with_vat, people);
    ESP_LOGI(TAG, "   5. แบ่งจ่าย (การหาร): %.2f ÷ %d = %.2f บาท/คน", total_with_vat, people, per_person);
    ESP_LOGI(TAG, "");
    
    // แสดงใบเสร็จ
    ESP_LOGI(TAG, "🧾 ใบเสร็จรับเงิน:");
    ESP_LOGI(TAG, "   ==========================================");
    ESP_LOGI(TAG, "   🏪 ตลาดสดใหม่ 🏪");
    ESP_LOGI(TAG, "   ==========================================");
    
    for (int i = 0; i < product_count; i++) {
        display_product(&products[i]);
    }
    
    ESP_LOGI(TAG, "   ----------------------------------------");
    ESP_LOGI(TAG, "   ยอดรวม:                    %.2f บาท", subtotal);
    ESP_LOGI(TAG, "   ส่วนลด (%.0f%%):             -%.2f บาท", discount_percent, subtotal - discounted_total);
    ESP_LOGI(TAG, "   ภาษี VAT (%.0f%%):            +%.2f บาท", vat_percent, total_with_vat - discounted_total);
    ESP_LOGI(TAG, "   ========================================");
    ESP_LOGI(TAG, "   ยอดสุทธิ:                   %.2f บาท", total_with_vat);
    ESP_LOGI(TAG, "   แบ่งจ่าย %d คน:              %.2f บาท/คน", people, per_person);
    ESP_LOGI(TAG, "   ========================================");
    ESP_LOGI(TAG, "   ขอบคุณที่ใช้บริการ 😊");
    ESP_LOGI(TAG, "📖 อ่านต่อในโปรเจคถัดไป: 06_advanced_math"); 
    
    vTaskDelay(2000 / portTICK_PERIOD_MS);
}
