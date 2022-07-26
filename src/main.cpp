#include <Windows.h>
#include <MinHook.h>
#include <gd.h>
#include <cocos2d.h>

using namespace cocos2d;

namespace PlayLayer {
	inline bool(__thiscall* init)(gd::PlayLayer* self, void* GJGameLevel);
	bool __fastcall hkInit(gd::PlayLayer* self, int edx, void* GJGameLevel);
}

bool __fastcall PlayLayer::hkInit(gd::PlayLayer* self, int edx, void* GJGameLevel)
{
    const auto winSize = CCDirector::sharedDirector()->getWinSize();

    CCLabelBMFont* cheatIndicator = CCLabelBMFont::create(".", "bigFont.fnt");
    cheatIndicator->setColor({0, 255, 0});
    cheatIndicator->setAnchorPoint({0.f, 0.5f});
    cheatIndicator->setPosition({5.f, winSize.height});
    cheatIndicator->setZOrder(99999);


    self->addChild(cheatIndicator);

    return init(self, GJGameLevel);
}


DWORD MainThread(LPVOID lpParam)
{

    MH_Initialize();

    MH_CreateHook(
        (PVOID)(gd::base + 0x01FB780),
        PlayLayer::hkInit,
        (LPVOID*)&PlayLayer::init
    );

    MH_EnableHook(MH_ALL_HOOKS);

    return S_OK;
}

DWORD __stdcall DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0x1000, reinterpret_cast<LPTHREAD_START_ROUTINE>(&MainThread), NULL, 0, NULL);
		break;
    case DLL_PROCESS_DETACH:
        break;
	default:
		break;
	}

	return TRUE;
}