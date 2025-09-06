#include "hud.h"
#include "cl_util.h"
#include "net_api.h"
#include "Discord.h"
#include "ClientDLL.h"

#define STEAM_APP_ID	"225840"
#define DISCORD_APP_ID	"396515353498484736"

// Own reimplementation based on decompile.

Discord::Discord()
{
	m_cClock = clock();
	GenerateParty();
}

Discord::~Discord()
{
}

void Discord::DiscordInitCVars()
{
	cl_discord = gEngfuncs.pfnRegisterVariable("cl_discord", "2", FCVAR_CLIENTDLL | FCVAR_ARCHIVE);
}

void Discord::GenerateParty()
{
}

void Discord::SetServername(const char* servername, int length, void* callback)
{

}

void Discord::DiscordUpdate()
{
}

void Discord::SetGamestatus(bool status)
{
	m_bGameStatus = status;

	if (!m_bGameStatus)
		GenerateParty();

	DiscordUpdateInfo();
}

void Discord::DiscordExit()
{
}

void Discord::DiscordInit() 
{
	DiscordEventHandlers handlers;
	memset(&handlers, 0, sizeof(handlers));
	handlers.ready = DiscordReady;
	handlers.disconnected = DiscordDisconnected;
	handlers.errored = DiscordError;
	handlers.joinGame = DiscordJoin;
	Discord_Initialize(DISCORD_APP_ID, &handlers, 1, STEAM_APP_ID);
}

void Discord::DiscordUpdateInfo()
{
	DiscordRichPresence presence{};
	char mapName[128];
	int playerCount = 0;
	cl_entity_t* client;
	char ipAddress[128];
	netadr_t addr;
	strcpy_s(mapName, gEngfuncs.pfnGetLevelName());

	presence.largeImageKey = "svenlogo";

	if (m_bGameStatus)
	{
		for (int i = 1; i < gEngfuncs.GetMaxClients(); i++)
		{
			client = gEngfuncs.GetEntityByIndex(i);

			if (client && client->player)
				playerCount++;
		}

		g_pEngineClient->GetServerAddress(&addr); // if I remember, there were issues there - ScriptedSnark

		if (addr.type)
		{
			strcpy_s(ipAddress, gEngfuncs.pNetAPI->AdrToString(&addr));
			presence.details = ipAddress;
		}

		presence.state = "In game";
		presence.largeImageText = mapName;
		presence.partySize = playerCount;
		presence.partyMax = gEngfuncs.GetMaxClients();
	}
	else
	{
		presence.state = "In menu";
	}

	Discord_UpdatePresence(&presence);
}

void Discord::DiscordDisconnected(int errorCode, const char* message)
{
	gEngfuncs.Con_DPrintf("[Discord] Disconnected (%d : %s)\n", errorCode, message); // TODO: replace Con_DPrintf
}

void Discord::DiscordError(int errorCode, const char* message)
{
	gEngfuncs.Con_DPrintf("[Discord] Error (%d : %s)\n", errorCode, message); // TODO: replace Con_DPrintf
}

void Discord::DiscordJoinRequest(const DiscordUser* request)
{
	//WTF?
	//Discord_Respond();
}

void Discord::DiscordSpectate(const char* spectateCode)
{
	;
}

void Discord::DiscordReady(const DiscordUser* user)
{

}

void Discord::DiscordJoin(const char* joinSecret)
{
	char cmd[128];

	gEngfuncs.Con_DPrintf("[Discord] Join: %s\n", joinSecret);
	sprintf_s(cmd, "connect %s", joinSecret);

	gEngfuncs.pfnClientCmd(cmd);
}