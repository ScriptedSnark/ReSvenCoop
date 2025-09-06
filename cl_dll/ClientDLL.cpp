#include "hud.h"
#include "cl_util.h"
#include "interface.h"
#include "ClientDLL.h"

IEngineClient* g_pEngineClient;

CClientDLL::CClientDLL()
{
}

CClientDLL::~CClientDLL()
{
}

void CClientDLL::Init(CreateInterfaceFn engineFactory)
{
	// TODO: replace prints with UTIL_HostError
	m_pEngineFactory = engineFactory;
	if (!engineFactory)
	{
		gEngfuncs.Con_DPrintf("Could not get Svengine factory.\n");
		return;
	}

	g_pEngineClient = (IEngineClient*)m_pEngineFactory(ENGINECLIENT_INTERFACE_VERSION, NULL);
	if (!g_pEngineClient)
	{
		gEngfuncs.Con_DPrintf("Unable to initialize Svengine client interface.\n");
		return;
	}
}

void CClientDLL::PlaySoundFX(float* pOrigin, int channel, char* sample, float volume, float attenuation, int flags, int pitch) 
{
}

void CClientDLL::RenderBegin(ref_params_s* ref_params)
{
}

void CClientDLL::RenderEnd()
{
}

EXPOSE_SINGLE_INTERFACE(CClientDLL, IClientDLL, CLIENTDLL_INTERFACE_VERSION);
