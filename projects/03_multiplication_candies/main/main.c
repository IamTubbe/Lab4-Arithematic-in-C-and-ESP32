#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "CANDIES_MATH";

void app_main(void)
{
    ESP_LOGI(TAG, "🍬 เริ่มต้นโปรแกรมนับลูกอมในถุง 🍬");
    ESP_LOGI(TAG, "====================================");
    
    // จำนวนลูกอมและถุง
    int candies_per_bag = 8;    
    int strawberry_bags = 3;
    int orange_bags = 2;
    int grape_bags = 4;

    int total_bags = strawberry_bags + orange_bags + grape_bags;
    int total_candies = total_bags * candies_per_bag;

    // แสดงข้อมูลลูกอมตามรส
    ESP_LOGI(TAG, "🍓 สตรอเบอร์รี่: %d ถุง = %d เม็ด", 
             strawberry_bags, strawberry_bags * candies_per_bag);
    ESP_LOGI(TAG, "🍊 รสส้ม: %d ถุง = %d เม็ด", 
             orange_bags, orange_bags * candies_per_bag);
    ESP_LOGI(TAG, "🍇 รสองุ่น: %d ถุง = %d เม็ด", 
             grape_bags, grape_bags * candies_per_bag);
    ESP_LOGI(TAG, "รวมถุงทั้งหมด %d ถุง = %d เม็ด", total_bags, total_candies);
    ESP_LOGI(TAG, "");

    vTaskDelay(1000 / portTICK_PERIOD_MS);

    // ตารางสูตรคูณของ candies_per_bag
    ESP_LOGI(TAG, "📊 ตารางสูตรคูณของ %d:", candies_per_bag);
    for (int i = 1; i <= 10; i++) {
        ESP_LOGI(TAG, "   %d x %d = %d", i, candies_per_bag, i * candies_per_bag);
    }
    ESP_LOGI(TAG, "");

    // แบบฝึกหัดที่ 4: แจกลูกอมให้เพื่อน
    int friends = 12;  
    int candies_per_friend = total_candies / friends;
    int remaining_candies = total_candies % friends;

    ESP_LOGI(TAG, "👥 แจกให้เพื่อน %d คน:", friends);
    ESP_LOGI(TAG, "   คนละ %d เม็ด", candies_per_friend);
    ESP_LOGI(TAG, "   เหลือ %d เม็ด", remaining_candies);
    ESP_LOGI(TAG, "");

    ESP_LOGI(TAG, "🎉 จบโปรแกรมนับลูกอมในถุง!");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}
