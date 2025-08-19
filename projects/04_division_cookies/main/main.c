#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "COOKIES_MATH";

void app_main(void)
{
    ESP_LOGI(TAG, "🍪 เริ่มต้นโปรแกรมแบ่งคุกกี้ 🍪");
    ESP_LOGI(TAG, "================================");

    // ประกาศตัวแปร
    int total_cookies = 12; // คุกกี้ทั้งหมด
    int friends = 6;        // จำนวนเพื่อน
    int cookies_per_person;  // คุกกี้ต่อคน
    int remaining_cookies;   // คุกกี้ที่เหลือ

    // แสดงโจทย์
    ESP_LOGI(TAG, "📖 โจทย์:");
    ESP_LOGI(TAG, "   มีคุกกี้: %d ชิ้น", total_cookies);
    ESP_LOGI(TAG, "   จะแบ่งให้เพื่อน: %d คน", friends);
    ESP_LOGI(TAG, "   ❓ แต่ละคนได้คุกกี้กี่ชิ้น?");
    ESP_LOGI(TAG, "");

    vTaskDelay(1000 / portTICK_PERIOD_MS);

    // ตรวจสอบการหารด้วยศูนย์
    if (friends == 0) {
        ESP_LOGE(TAG, "❌ ข้อผิดพลาด: ไม่สามารถหารด้วยศูนย์ได้!");
        ESP_LOGI(TAG, "   คุกกี้ทั้งหมด %d ชิ้น จะเหลือไว้ทั้งหมด", total_cookies);
        ESP_LOGI(TAG, "🎉 จบโปรแกรม!");
        return;
    }

    // คำนวณผลลัพธ์
    cookies_per_person = total_cookies / friends;
    remaining_cookies = total_cookies % friends;

    // แสดงขั้นตอนการคิด
    ESP_LOGI(TAG, "🧮 ขั้นตอนการคิด:");
    ESP_LOGI(TAG, "   คุกกี้ทั้งหมด ÷ จำนวนเพื่อน = %d ÷ %d", total_cookies, friends);
    ESP_LOGI(TAG, "   = %d ชิ้นต่อคน", cookies_per_person);
    if (remaining_cookies > 0) {
        ESP_LOGI(TAG, "   เศษที่เหลือ = %d ชิ้น", remaining_cookies);
    }
    ESP_LOGI(TAG, "");

    // แสดงคำตอบ
    ESP_LOGI(TAG, "✅ คำตอบ:");
    ESP_LOGI(TAG, "   แต่ละคนได้คุกกี้ %d ชิ้น", cookies_per_person);
    if (remaining_cookies > 0) {
        ESP_LOGI(TAG, "   มีคุกกี้เหลือ %d ชิ้น (ไม่สามารถแบ่งเท่าๆ กัน)", remaining_cookies);
    } else {
        ESP_LOGI(TAG, "   แบ่งได้พอดี ไม่มีเหลือ");
    }

    // ตรวจสอบว่าหารลงตัวไหม
    if (remaining_cookies == 0) {
        ESP_LOGI(TAG, "✅ หารลงตัว! ทุกคนได้เท่ากัน");
    } else {
        ESP_LOGI(TAG, "⚠️ หารไม่ลงตัว! เหลือ %d ชิ้น", remaining_cookies);
    }
    ESP_LOGI(TAG, "");

    // แสดงภาพประกอบการแบ่ง
    ESP_LOGI(TAG, "🎨 ภาพประกอบการแบ่ง:");
    printf("   คุกกี้ทั้งหมด: ");
    for (int i = 0; i < total_cookies; i++) {
        printf("🍪");
    }
    printf(" (%d ชิ้น)\n\n", total_cookies);

    // แสดงการแบ่งให้แต่ละคน
    for (int person = 1; person <= friends; person++) {
        printf("   เพื่อนคนที่ %d: ", person);
        for (int c = 0; c < cookies_per_person; c++) {
            printf("🍪");
        }
        printf(" (%d ชิ้น)\n", cookies_per_person);
    }

    // แสดงคุกกี้ที่เหลือ
    if (remaining_cookies > 0) {
        printf("   เหลือ: ");
        for (int i = 0; i < remaining_cookies; i++) {
            printf("🍪");
        }
        printf(" (%d ชิ้น)\n", remaining_cookies);
    }

    ESP_LOGI(TAG, "");

    // แบบฝึกหัดที่ 3: หาจำนวนเพื่อนที่เหมาะสม
    int cookies = 30;
    ESP_LOGI(TAG, "🔍 คุกกี้ %d ชิ้น หารลงตัวกับ:", cookies);

    for (int people = 1; people <= 10; people++) {
        if (cookies % people == 0) {
            ESP_LOGI(TAG, "   ✅ %d คน → คนละ %d ชิ้น", 
                 people, cookies / people);
        }
    }

    ESP_LOGI(TAG, "");
    ESP_LOGI(TAG, "🎉 จบโปรแกรมแบ่งคุกกี้!");
    ESP_LOGI(TAG, "📖 อ่านต่อในโปรเจคถัดไป: 05_mixed_shopping");
}
