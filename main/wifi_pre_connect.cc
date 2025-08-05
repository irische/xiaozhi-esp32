#include <esp_log.h>
#include <string>
#include <ssid_manager.h>            // 用于管理SSID列表

#define TAG "wifi_pre_connect"

// 伪函数：模拟从外部API获取WiFi账号密码
// 实际使用时请替换为真实API调用
void GetWifiCredentialsFromApi(std::string& ssid, std::string& password) {
    // TODO: 替换为实际的API获取逻辑
    // 例如：通过HTTP请求、蓝牙、串口等方式获取
    ssid = "Chrissy";   //"antop-r02";       
    password = "11111111";//"antop@88888";   
    ESP_LOGI(TAG, "[模拟] 已从API获取WiFi账号密码: SSID=%s, PASSWORD=%s", ssid.c_str(), password.c_str());
}

extern "C" void WifiPreConnect() {
    ESP_LOGI(TAG, "=== 进入WifiPreConnect，准备自动联网 ===");
    
    // 从外部API获取WiFi账号密码
    std::string ssid, password;
    GetWifiCredentialsFromApi(ssid, password);

    if (ssid.empty() || password.empty()) {
        ESP_LOGE(TAG, "未获取到有效的WiFi账号或密码，跳过自动联网");
        return;
    }

    ESP_LOGI(TAG, "获取到WiFi凭据: SSID=%s", ssid.c_str());

    // ===== 修改：只使用SsidManager保存凭据，不进行底层WiFi操作 =====
    ESP_LOGI(TAG, "保存WiFi凭据到SsidManager...");
    SsidManager::GetInstance().AddSsid(ssid, password);
    ESP_LOGI(TAG, "WiFi凭据已保存到SsidManager: SSID=%s", ssid.c_str());
    
    // 清除force_ap标志，确保不会强制进入配网模式
    // 注意：这里不进行WiFi连接，让WifiBoard和WifiStation处理连接
    ESP_LOGI(TAG, "WiFi凭据已保存，继续正常启动流程");
} 