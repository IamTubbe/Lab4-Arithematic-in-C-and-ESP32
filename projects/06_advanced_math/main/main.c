#include <stdio.h>
#include <math.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// 🏷️ Tag สำหรับ Log
static const char *TAG = "ADVANCED_MATH";

// 🔢 ค่าคงที่ทางคณิตศาสตร์
#define PI 3.14159265359
#define SQUARE_METERS_TO_RAI 1600.0  // 1 ไร่ = 1,600 ตร.ม.

// 📐 โครงสร้างข้อมูลรูปทรง
typedef struct {
    char name[50];
    double length;      // ความยาว/รัศมี
    double width;       // ความกว้าง
    double height;      // ความสูง/ความลึก
} shape_t;

// 🏟️ ฟังก์ชันคำนวณสี่เหลี่ยม
void calculate_rectangle(shape_t shape) {
    double area = shape.length * shape.width;
    double perimeter = 2 * (shape.length + shape.width);
    double area_in_rai = area / SQUARE_METERS_TO_RAI;
    
    ESP_LOGI(TAG, "╔══════════════════════════════════════╗");
    ESP_LOGI(TAG, "║          %s           ║", shape.name);
    ESP_LOGI(TAG, "╠══════════════════════════════════════╣");
    ESP_LOGI(TAG, "║ 📏 ความยาว: %.2f เมตร", shape.length);
    ESP_LOGI(TAG, "║ 📏 ความกว้าง: %.2f เมตร", shape.width);
    ESP_LOGI(TAG, "║ 📐 พื้นที่: %.2f × %.2f = %.2f ตร.ม.", 
             shape.length, shape.width, area);
    ESP_LOGI(TAG, "║ 🔄 ปริเมตร: 2×(%.0f+%.0f) = %.2f ม.", 
             shape.length, shape.width, perimeter);
    ESP_LOGI(TAG, "║ 🌾 เท่ากับ: %.4f ไร่", area_in_rai);
    ESP_LOGI(TAG, "╚══════════════════════════════════════╝");
}

// 🏊‍♀️ ฟังก์ชันคำนวณวงกลม
void calculate_circle(shape_t shape) {
    double radius = shape.length;  // ใช้ length เป็น radius
    double surface_area = PI * radius * radius;
    double circumference = 2 * PI * radius;
    double volume = surface_area * shape.height;  // ปริมาตรทรงกระบอก
    
    ESP_LOGI(TAG, "╔══════════════════════════════════════╗");
    ESP_LOGI(TAG, "║          %s            ║", shape.name);
    ESP_LOGI(TAG, "╠══════════════════════════════════════╣");
    ESP_LOGI(TAG, "║ 📏 รัศมี: %.2f เมตร", radius);
    ESP_LOGI(TAG, "║ 📏 ความลึก: %.2f เมตร", shape.height);
    ESP_LOGI(TAG, "║ 🌊 พื้นที่ผิวน้ำ: π × %.0f² = %.2f ตร.ม.", 
             radius, surface_area);
    ESP_LOGI(TAG, "║ ⭕ เส้นรอบวง: 2π × %.0f = %.2f ม.", 
             radius, circumference);
    ESP_LOGI(TAG, "║ 💧 ปริมาตรน้ำ: %.2f × %.2f = %.2f ลบ.ม.", 
             surface_area, shape.height, volume);
    ESP_LOGI(TAG, "╚══════════════════════════════════════╝");
}

// 🎁 ฟังก์ชันคำนวณทรงผีเสื้อ
void calculate_box(shape_t shape) {
    double volume = shape.length * shape.width * shape.height;
    double surface_area = 2 * (shape.length * shape.width + 
                               shape.width * shape.height + 
                               shape.length * shape.height);
    
    ESP_LOGI(TAG, "╔══════════════════════════════════════╗");
    ESP_LOGI(TAG, "║          %s          ║", shape.name);
    ESP_LOGI(TAG, "╠══════════════════════════════════════╣");
    ESP_LOGI(TAG, "║ 📏 ความยาว: %.2f ซม.", shape.length);
    ESP_LOGI(TAG, "║ 📏 ความกว้าง: %.2f ซม.", shape.width);
    ESP_LOGI(TAG, "║ 📏 ความสูง: %.2f ซม.", shape.height);
    ESP_LOGI(TAG, "║ 📦 ปริมาตร: %.0f×%.0f×%.0f = %.2f ลบ.ซม.", 
             shape.length, shape.width, shape.height, volume);
    ESP_LOGI(TAG, "║ 🎀 พื้นที่ผิว: %.2f ตร.ซม.", surface_area);
    ESP_LOGI(TAG, "║ 📐 เท่ากับ: %.6f ลิตร", volume / 1000.0);
    ESP_LOGI(TAG, "╚══════════════════════════════════════╝");
}

// 📊 ฟังก์ชันเปรียบเทียบผลลัพธ์
void compare_results(void) {
    ESP_LOGI(TAG, "\n🔍 การเปรียบเทียบผลลัพธ์:");
    ESP_LOGI(TAG, "╔════════════════════════════════════╗");
    ESP_LOGI(TAG, "║  สนามฟุตบอล vs สระน้ำ vs กล่อง    ║");
    ESP_LOGI(TAG, "╠════════════════════════════════════╣");
    ESP_LOGI(TAG, "║ 🏟️ สนาม: ใหญ่ที่สุด (6,000 ตร.ม.)  ║");
    ESP_LOGI(TAG, "║ 🏊‍♀️ สระ: กลาง (78.54 ตร.ม.)       ║");
    ESP_LOGI(TAG, "║ 🎁 กล่อง: เล็กที่สุด (300 ลบ.ซม.)  ║");
    ESP_LOGI(TAG, "╚════════════════════════════════════╝");
}

// 🎓 ฟังก์ชันแสดงความรู้เพิ่มเติม
void show_math_facts(void) {
    ESP_LOGI(TAG, "\n📚 ความรู้ทางคณิตศาสตร์:");
    ESP_LOGI(TAG, "╔═══════════════════════════════════════╗");
    ESP_LOGI(TAG, "║           สูตรคณิตศาสตร์             ║");
    ESP_LOGI(TAG, "╠═══════════════════════════════════════╣");
    ESP_LOGI(TAG, "║ 📐 สี่เหลี่ยม: พื้นที่ = ยาว × กว้าง   ║");
    ESP_LOGI(TAG, "║ ⭕ วงกลม: พื้นที่ = π × r²           ║");
    ESP_LOGI(TAG, "║ 📦 ทรงผีเสื้อ: ปริมาตร = ย×ก×ส       ║");
    ESP_LOGI(TAG, "║ 💡 π (pi) ≈ 3.14159                  ║");
    ESP_LOGI(TAG, "║ 🌾 1 ไร่ = 1,600 ตารางเมตร          ║");
    ESP_LOGI(TAG, "╚═══════════════════════════════════════╝");
}

// 🎯 ฟังก์ชันท้าทาย - คำนวณสามเหลี่ยม
void calculate_triangle_bonus(void) {
    double base = 10.0;     // ฐาน
    double height = 8.0;    // สูง
    double side1 = 10.0;    // ด้านที่ 1
    double side2 = 8.0;     // ด้านที่ 2
    double side3 = 6.0;     // ด้านที่ 3
    
    double area = 0.5 * base * height;
    double perimeter = side1 + side2 + side3;
    
    ESP_LOGI(TAG, "\n🎯 โบนัส: สามเหลี่ยม");
    ESP_LOGI(TAG, "╔═══════════════════════════════════════╗");
    ESP_LOGI(TAG, "║         สามเหลี่ยมมุมฉาก             ║");
    ESP_LOGI(TAG, "╠═══════════════════════════════════════╣");
    ESP_LOGI(TAG, "║ 📏 ฐาน: %.2f ซม.", base);
    ESP_LOGI(TAG, "║ 📏 สูง: %.2f ซม.", height);
    ESP_LOGI(TAG, "║ 📐 พื้นที่: ½×%.0f×%.0f = %.2f ตร.ซม.", 
             base, height, area);
    ESP_LOGI(TAG, "║ 🔄 ปริเมตร: %.0f+%.0f+%.0f = %.2f ซม.", 
             side1, side2, side3, perimeter);
    ESP_LOGI(TAG, "╚═══════════════════════════════════════╝");
}

// 🔺 ฟังก์ชันคำนวณสามเหลี่ยม
void calculate_triangle(shape_t shape) {
    double area = 0.5 * shape.length * shape.height; // length=ฐาน, height=สูง
    double perimeter = shape.length + shape.width + shape.height; // width = ด้านเอียง

    ESP_LOGI(TAG, "\n🔺 การคำนวณสามเหลี่ยม");
    ESP_LOGI(TAG, "╔══════════════════════════════════════╗");
    ESP_LOGI(TAG, "║              %s               ║", shape.name);
    ESP_LOGI(TAG, "╠══════════════════════════════════════╣");
    ESP_LOGI(TAG, "║ 📏 ฐาน: %.2f เมตร", shape.length);
    ESP_LOGI(TAG, "║ 📏 สูง: %.2f เมตร", shape.height);
    ESP_LOGI(TAG, "║ 📐 พื้นที่: ½×%.0f×%.0f = %.2f ตร.ม.", 
             shape.length, shape.height, area);
    ESP_LOGI(TAG, "║ 🔄 ปริเมตร (โดยประมาณ): %.2f เมตร", perimeter);
    ESP_LOGI(TAG, "╚══════════════════════════════════════╝");
}

// 🌀 ฟังก์ชันคำนวณทรงกรวย
void calculate_cone(shape_t shape) {
    double radius = shape.length;  // length = รัศมี
    double height = shape.height;
    double volume = (PI * radius * radius * height) / 3.0;
    double slant_height = sqrt(radius * radius + height * height);
    double surface_area = PI * radius * (radius + slant_height);

    ESP_LOGI(TAG, "\n🌀 การคำนวณทรงกรวย");
    ESP_LOGI(TAG, "╔══════════════════════════════════════╗");
    ESP_LOGI(TAG, "║              %s             ║", shape.name);
    ESP_LOGI(TAG, "╠══════════════════════════════════════╣");
    ESP_LOGI(TAG, "║ 📏 รัศมี: %.2f เมตร", radius);
    ESP_LOGI(TAG, "║ 📏 สูง: %.2f เมตร", height);
    ESP_LOGI(TAG, "║ 🧮 ปริมาตร: (1/3)πr²h = %.2f ลบ.ม.", volume);
    ESP_LOGI(TAG, "║ 📐 พื้นที่ผิว: %.2f ตร.ม.", surface_area);
    ESP_LOGI(TAG, "╚══════════════════════════════════════╝");
}

// 🌾 ฟังก์ชันแปลงหน่วยพื้นที่ (ตร.ม. → ไร่)
void convert_area(double sqm) {
    double rai = sqm / SQUARE_METERS_TO_RAI;
    ESP_LOGI(TAG, "\n🌾 การแปลงหน่วยพื้นที่");
    ESP_LOGI(TAG, "╔══════════════════════════════════════╗");
    ESP_LOGI(TAG, "║        แปลงจาก ตารางเมตร → ไร่      ║");
    ESP_LOGI(TAG, "╠══════════════════════════════════════╣");
    ESP_LOGI(TAG, "║ 📐 %.2f ตร.ม.", sqm);
    ESP_LOGI(TAG, "║ 🌾 เท่ากับ %.4f ไร่", rai);
    ESP_LOGI(TAG, "╚══════════════════════════════════════╝");
}

void app_main(void) {
    ESP_LOGI(TAG, "🚀 เริ่มต้นโปรแกรมคณิตศาสตร์ขั้นสูง!");
    ESP_LOGI(TAG, "📐 การคำนวณพื้นที่และปริมาตร\n");
    
    vTaskDelay(pdMS_TO_TICKS(1000));
    
    // 🏟️ สนามฟุตบอล
    shape_t football_field = {
        .name = "สนามฟุตบอล",
        .length = 100.0,
        .width = 60.0,
        .height = 0.0
    };
    
    // 🏊‍♀️ สระน้ำกลม
    shape_t swimming_pool = {
        .name = "สระน้ำกลม",
        .length = 5.0,    // รัศมี
        .width = 0.0,
        .height = 2.0     // ความลึก
    };
    
    // 🎁 กล่องของขวัญ
    shape_t gift_box = {
        .name = "กล่องของขวัญ",
        .length = 20.0,
        .width = 15.0,
        .height = 10.0
    };

    // 🔺 สามเหลี่ยม
    shape_t triangle_shape = {
        .name = "สามเหลี่ยมมุมฉาก",
        .length = 10.0,  // ฐาน
        .width = 6.0,    // ด้านเอียง (ประมาณ)
        .height = 8.0    // สูง
    };
    
    // 🌀 ทรงกรวย
    shape_t cone_shape = {
        .name = "ทรงกรวย",
        .length = 3.0,   // รัศมี
        .width = 0.0,
        .height = 4.0    // สูง
    };
    
    // 🎨 ASCII Art
    ESP_LOGI(TAG, "   🏟️     🏊‍♀️     🎁     🔺     🌀");
    ESP_LOGI(TAG, " ┌─────┐  ╭─────╮  ┌─────┐  ┌─────┐  ╭─────╮");
    ESP_LOGI(TAG, " │ ⚽  │  │ 💧💧 │  │ 🎀  │  │ ▲  │  │ 🌀  │");
    ESP_LOGI(TAG, " │     │  │     │  │     │  │     │  │     │");
    ESP_LOGI(TAG, " └─────┘  ╰─────╯  └─────┘  └─────┘  ╰─────╯\n");
    
    // ✅ คำนวณ
    calculate_rectangle(football_field);
    convert_area(football_field.length * football_field.width); // แปลงเป็นไร่
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    calculate_circle(swimming_pool);
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    calculate_box(gift_box);
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    calculate_triangle(triangle_shape);
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    calculate_cone(cone_shape);
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    compare_results();
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    show_math_facts();
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    calculate_triangle_bonus();
    
    ESP_LOGI(TAG, "\n✅ เสร็จสิ้นการคำนวณทั้งหมด!");
    ESP_LOGI(TAG, "🎓 ได้เรียนรู้: คณิตศาสตร์ขั้นสูง, struct, #define, และฟังก์ชันคณิตศาสตร์");
}

