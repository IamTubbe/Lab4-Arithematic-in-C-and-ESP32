#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// กำหนดชื่อสำหรับแสดงใน log
static const char *TAG = "APPLE_MATH";

void app_main(void)
{
    ESP_LOGI(TAG, "🍎 เริ่มต้นโปรแกรมนับแอปเปิ้ลในตะกร้า 🍎");
    ESP_LOGI(TAG, "==========================================");
    
    // ประกาศตัวแปรเก็บจำนวนแอปเปิ้ล
    int apples_in_basket = 5;   // แอปเปิ้ลที่มีอยู่แล้วในตะกร้า
    int apples_added = 4;       // แอปเปิ้ลที่ใส่เพิ่มเข้ามา
    int total_apples;           // แอปเปิ้ลรวมทั้งหมด
    int green_apples = 3;       // แอปเปิ้ลเขียว (อีกตะกร้า)
    int total_all_apples;       // แอปเปิ้ลรวมทั้งหมด (แดง + เขียว)
    
    // แสดงข้อมูลเริ่มต้น
    ESP_LOGI(TAG, "📖 โจทย์:");
    ESP_LOGI(TAG, "   ในตะกร้ามีแอปเปิ้ลแดงแล้ว: %d ผล", apples_in_basket);
    ESP_LOGI(TAG, "   มีคนใส่เพิ่มเข้ามาอีก: %d ผล", apples_added);
    ESP_LOGI(TAG, "   ❓ ตอนนี้มีแอปเปิ้ลแดงรวมกี่ผล?");
    ESP_LOGI(TAG, "");
    
    // รอสักครู่เพื่อให้อ่านโจทย์
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    
    // คำนวณผลรวม
    total_apples = apples_in_basket + apples_added;
    total_all_apples = total_apples + green_apples;

    // แสดงผลแอปเปิ้ลเขียว
    ESP_LOGI(TAG, "🍏 และยังมีแอปเปิ้ลเขียวอีก: %d ผล", green_apples);
    ESP_LOGI(TAG, "🍎 แอปเปิ้ลทั้งหมด (แดง+เขียว): %d ผล", total_all_apples);
    
    // แสดงขั้นตอนการคิด
    ESP_LOGI(TAG, "🧮 ขั้นตอนการคิด:");
    ESP_LOGI(TAG, "   แอปเปิ้ลแดงที่มีอยู่ + แอปเปิ้ลแดงที่ใส่เพิ่ม");
    ESP_LOGI(TAG, "   = %d + %d", apples_in_basket, apples_added);
    ESP_LOGI(TAG, "   = %d ผล", total_apples);
    ESP_LOGI(TAG, "");
    
    // แสดงคำตอบ
    ESP_LOGI(TAG, "✅ คำตอบ:");
    ESP_LOGI(TAG, "   ตอนนี้มีแอปเปิ้ลแดงทั้งหมด %d ผล", total_apples);
    ESP_LOGI(TAG, "");
    
    // แสดงภาพประกอบ (ASCII Art)
    ESP_LOGI(TAG, "🎨 ภาพประกอบ:");
    ESP_LOGI(TAG, "   แอปเปิ้ลเดิม (แดง): 🍎🍎🍎🍎🍎 (%d ผล)", apples_in_basket);
    ESP_LOGI(TAG, "   แอปเปิ้ลเพิ่ม (แดง): 🍎🍎🍎🍎 (%d ผล)", apples_added);
    ESP_LOGI(TAG, "   รวมแอปเปิ้ลแดง:      🍎 x %d ผล", total_apples);
    ESP_LOGI(TAG, "   แอปเปิ้ลเขียว:        🍏🍏🍏 (%d ผล)", green_apples);
    ESP_LOGI(TAG, "   รวมทั้งหมด:           🍎🍏 x %d ผล", total_all_apples);
    ESP_LOGI(TAG, "");
    
    // ตัวอย่างเพิ่มเติม
    ESP_LOGI(TAG, "💡 ตัวอย่างเพิ่มเติม:");
    
    // ตัวอย่างที่ 1
    int example1_old = 6;
    int example1_new = 2;
    int example1_total = example1_old + example1_new;
    ESP_LOGI(TAG, "   ถ้ามีแอปเปิ้ล %d ผล และมีคนใส่เพิ่ม %d ผล", example1_old, example1_new);
    ESP_LOGI(TAG, "   จะได้แอปเปิ้ลทั้งหมด %d + %d = %d ผล", example1_old, example1_new, example1_total);
    ESP_LOGI(TAG, "");
    
    // ตัวอย่างที่ 2
    int example2_old = 9;
    int example2_new = 5;
    int example2_total = example2_old + example2_new;
    ESP_LOGI(TAG, "   ถ้ามีแอปเปิ้ล %d ผล และมีคนใส่เพิ่ม %d ผล", example2_old, example2_new);
    ESP_LOGI(TAG, "   จะได้แอปเปิ้ลทั้งหมด %d + %d = %d ผล", example2_old, example2_new, example2_total);
    ESP_LOGI(TAG, "");
    
    // สรุปการเรียนรู้
    ESP_LOGI(TAG, "📚 สิ่งที่เรียนรู้:");
    ESP_LOGI(TAG, "   1. การบวกเลข (Addition): a + b = c");
    ESP_LOGI(TAG, "   2. การใช้ตัวแปร (Variables) เก็บค่า");
    ESP_LOGI(TAG, "   3. การแสดงผลด้วย ESP_LOGI");
    ESP_LOGI(TAG, "   4. การแก้โจทย์ด้วยสถานการณ์ใหม่");
    ESP_LOGI(TAG, "");
    
    ESP_LOGI(TAG, "🎉 จบโปรแกรมนับแอปเปิ้ล!");
    ESP_LOGI(TAG, "📖 อ่านต่อในโปรเจคถัดไป: 04_subtraction_mangoes");
    
    // รอสักครู่ก่อนจบโปรแกรม
    vTaskDelay(2000 / portTICK_PERIOD_MS);
}
