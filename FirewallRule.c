#include <Windows.h>
#include <stdio.h>
#include <netfw.h>

int main() {
    HRESULT hr;
  
  //COM library initializing
    hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    if (FAILED(hr)) {
        printf("Could not initialize COM library.\n");
        return 1;
    }

    //creating an instance of the Windows Firewall API
    //instance 
    INetFwPolicy2* firewallPolicy;
    hr = CoCreateInstance(__uuidof(NetFwPolicy2), NULL, CLSCTX_INPROC_SERVER, __uuidof(INetFwPolicy2), (void**)&firewallPolicy);
    if (FAILED(hr)) {
        printf("Could not create instance of Windows Firewall API.\n");
        CoUninitialize();
        return 1;
    }

    INetFwProfile* currentProfile;
    hr = firewallPolicy->get_CurrentProfile(&currentProfile);
    if (FAILED(hr)) {
        printf("Could not get current profile of Windows Firewall.\n");
        firewallPolicy->Release();
        CoUninitialize();
        return 1;
    }

    //Your Rule here
    INetFwRule* blockRule;
    hr = CoCreateInstance(__uuidof(NetFwRule), NULL, CLSCTX_INPROC_SERVER, __uuidof(INetFwRule), (void**)&blockRule);
    if (FAILED(hr)) {
        printf("Could not create instance of Windows Firewall rule.\n");
        currentProfile->Release();
        firewallPolicy->Release();
        CoUninitialize();
        return 1;
    }

    //Blocking the Application
    blockRule->put_Name(L"Block Application");
    blockRule->put_ApplicationName(L"C:\\Path\\To\\Your\\Application.exe");
    blockRule->put_Action(NET_FW_ACTION_BLOCK);
    blockRule->put_Enabled(VARIANT_TRUE);

    // Adding rule to firewall
    INetFwRules* firewallRules;
    hr = firewallPolicy->get_Rules(&firewallRules);
    if (FAILED(hr)) {
        printf("Could not get rules collection of Windows Firewall.\n");
        blockRule->Release();
        currentProfile->Release();
        firewallPolicy->Release();
        CoUninitialize();
        return 1;
    }

    hr = firewallRules->Add(blockRule);
    if (FAILED(hr)) {
        printf("Could not add rule to Windows Firewall.\n");
        firewallRules->Release();
        blockRule->Release();
        currentProfile->Release();
        firewallPolicy->Release();
        CoUninitialize();
        return 1;
    }

    firewallRules->Release();
    blockRule->Release();
    currentProfile->Release();
    firewallPolicy->Release();
    CoUninitialize();

    printf("Application blocked successfully!\n");

    return 0;
}
