#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "TOYS_MATH";

void app_main(void)
{
    ESP_LOGI(TAG, "🧸 เริ่มต้นโปรแกรมนับของเล่นของน้อง (Multiplication & Subtraction) 🧸");
    ESP_LOGI(TAG, "=================================================================");

    // ข้อมูลโจทย์
    int friends = 10;           // เพื่อนทั้งหมด
    int toys_per_friend = 2;    // ของเล่นที่ให้เพื่อนแต่ละคน
    int toys_have = 15;         // ของเล่นที่มีอยู่จริง

    // คำนวณของเล่นที่ต้องใช้
    int toys_required = friends * toys_per_friend;

    ESP_LOGI(TAG, "📖 โจทย์:");
    ESP_LOGI(TAG, "   เพื่อนทั้งหมด: %d คน", friends);
    ESP_LOGI(TAG, "   แจกคนละ: %d ชิ้น", toys_per_friend);
    ESP_LOGI(TAG, "   ต้องใช้ของเล่นทั้งหมด: %d ชิ้น", toys_required);
    ESP_LOGI(TAG, "   ของเล่นที่น้องมีอยู่จริง: %d ชิ้น", toys_have);
    ESP_LOGI(TAG, "");

    vTaskDelay(2000 / portTICK_PERIOD_MS);

    // ตรวจสอบว่าของเล่นพอหรือไม่
    if (toys_have >= toys_required) {
        ESP_LOGI(TAG, "✅ ของเล่นพอแจก!");
        ESP_LOGI(TAG, "   หลังแจก จะเหลือ %d ชิ้น", toys_have - toys_required);
    } else {
        int shortage = toys_required - toys_have;
        ESP_LOGW(TAG, "❌ ของเล่นไม่พอ!");
        ESP_LOGI(TAG, "   ต้องการ %d ชิ้น แต่มีแค่ %d ชิ้น", toys_required, toys_have);
        ESP_LOGI(TAG, "   ขาดไป %d ชิ้น", shortage);
    }

    ESP_LOGI(TAG, "");
    ESP_LOGI(TAG, "🧮 ขั้นตอนการคิด:");
    ESP_LOGI(TAG, "   ของเล่นที่ต้องใช้ = เพื่อน x ของเล่นต่อคน");
    ESP_LOGI(TAG, "   = %d x %d", friends, toys_per_friend);
    ESP_LOGI(TAG, "   = %d ชิ้น", toys_required);

    ESP_LOGI(TAG, "");
    ESP_LOGI(TAG, "📚 สิ่งที่เรียนรู้:");
    ESP_LOGI(TAG, "   1. การคูณเลข (Multiplication)");
    ESP_LOGI(TAG, "   2. การลบเลข (Subtraction)");
    ESP_LOGI(TAG, "   3. การใช้ if-else ตรวจสอบเงื่อนไข");
    ESP_LOGI(TAG, "");

    ESP_LOGI(TAG, "🎉 จบโปรแกรมแบบฝึกหัดที่ 4!");
}
