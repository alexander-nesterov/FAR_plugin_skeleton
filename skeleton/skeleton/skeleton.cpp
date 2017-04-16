#include "stdafx.h"
#include <windows.h>
#include <initguid.h>
#include "SDK/plugin.hpp"
#include "SDK/farcolor.hpp"
#include "SDK/DlgBuilder.hpp"
#include "Headers/version.hpp"
#include "Headers/guid.hpp"

static struct PluginStartupInfo Info;

enum {
	MTitle,
};

const wchar_t *GetMsg(int MsgId);

/****************************************************************************
***************************** Exported functions ***************************
****************************************************************************/

void WINAPI GetGlobalInfoW(struct GlobalInfo *Info)
{
	Info->StructSize = sizeof(struct GlobalInfo);
	Info->MinFarVersion = FARMANAGERVERSION;
	Info->Version = PLUGIN_VERSION;
	Info->Guid = MainGuid;
	Info->Title = PLUGIN_NAME;
	Info->Description = PLUGIN_DESC;
	Info->Author = PLUGIN_AUTHOR;
}

/****************************************************************************
Функция GetMsg возвращает строку сообщения из языкового файла.
https://api.farmanager.com/ru/service_functions/getmsg.html
****************************************************************************/
const wchar_t *GetMsg(int MsgId)
{
	return Info.GetMsg(&MainGuid, MsgId);
}

/****************************************************************************
Функция SetStartupInfoW вызывается один раз, после загрузки DLL-модуля в память. 
Far Manager передаёт плагину информацию, необходимую для дальнейшей работы.
https://api.farmanager.com/ru/exported_functions/setstartupinfow.html
****************************************************************************/
void WINAPI SetStartupInfoW(const struct PluginStartupInfo *psi)
{
	Info = *psi;
}

/****************************************************************************
Функция GetPluginInfoW вызывается Far Manager для получения дополнительной информации о плагине.
https://api.farmanager.com/ru/exported_functions/getplugininfow.html
****************************************************************************/
void WINAPI GetPluginInfoW(struct PluginInfo *Info)
{
	Info->StructSize = sizeof(*Info);
	Info->Flags = PF_EDITOR;
	static const wchar_t *PluginMenuStrings[1];
	PluginMenuStrings[0] = GetMsg(MTitle);
	Info->PluginMenu.Guids = &MenuGuid;
	Info->PluginMenu.Strings = PluginMenuStrings;
	Info->PluginMenu.Count = ARRAYSIZE(PluginMenuStrings);
}

/****************************************************************************
Функция OpenW вызывается Far Manager'ом для запуска плагина.
https://api.farmanager.com/ru/exported_functions/openw.html
****************************************************************************/
HANDLE WINAPI OpenW(const struct OpenInfo *OInfo)
{
	Info.Message(
		&MainGuid,
		&MsgGuid,
		FMSG_ALLINONE | FMSG_MB_OKCANCEL,
		L"HelpTopic",
		(const wchar_t * const *)L"Skeleton Menu\nItem1\nItem2\nItem3",
		0, 0);

	return NULL;
}

