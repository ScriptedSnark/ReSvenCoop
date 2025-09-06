#ifndef DISCORD_H
#define DISCORD_H

#include "discord_rpc.h"
#include "time.h"

class Discord
{
public:
	Discord();
	~Discord();
	void DiscordInitCVars();
	void GenerateParty();
	void SetServername(const char*, int, void*);
	void DiscordUpdate();
	void SetGamestatus(bool);
	void DiscordExit();
	void DiscordInit();
	void DiscordUpdateInfo();

	static void DiscordDisconnected(int, const char*);
	static void DiscordError(int, const char*);
	static void DiscordJoinRequest(const DiscordUser*);
	static void DiscordSpectate(const char*);
	static void DiscordReady(const DiscordUser*);
	static void DiscordJoin(const char*);
private:
	cvar_t* cl_discord = nullptr;
	bool m_bGameStatus;
	clock_t m_cClock;
};

extern Discord* g_pDiscord;

#endif // DISCORD_H