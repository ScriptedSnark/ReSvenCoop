#ifndef CLIENTDLL_H
#define CLIENTDLL_H

#include "IEngineClient.h"
#include "ref_params.h"

class IClientDLL : public IBaseInterface
{
public:
	virtual void Init(CreateInterfaceFn engineFactory) = 0;
	virtual void PlaySoundFX(float* pOrigin, int channel, char* sample, float volume, float attenuation, int flags, int pitch) = 0;
	virtual void RenderBegin(ref_params_s* ref_params) = 0;
	virtual void RenderEnd() = 0;
};

class CClientDLL : public IClientDLL
{
public:
	CClientDLL();
	~CClientDLL();

	virtual void Init(CreateInterfaceFn engineFactory);
	virtual void PlaySoundFX(float* pOrigin, int channel, char* sample, float volume, float attenuation, int flags, int pitch);
	virtual void RenderBegin(ref_params_s* ref_params);
	virtual void RenderEnd();

private:
	CreateInterfaceFn m_pEngineFactory;
};

#define CLIENTDLL_INTERFACE_VERSION "SCClientDLL001"

#endif // CLIENTDLL_H