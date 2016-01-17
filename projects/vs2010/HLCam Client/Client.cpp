#include "Client.hpp"
#include <vector>

#include "hud.h"
#include "cl_util.h"
#include "parsemsg.h"
#include "vgui_TeamFortressViewport.h"

namespace
{
	struct HLCamClient
	{
		std::vector<Cam::ClientCamera> Cameras;
		std::vector<Cam::ClientTrigger> Triggers;
	};

	static HLCamClient TheCamClient;
}

int HLCamClient_OnCameraCreatedMessage(const char* name, int size, void* buffer)
{
	BEGIN_READ(buffer, size);

	return 1;
}

int HLCamClient_OnTriggerCreatedMessage(const char* name, int size, void* buffer)
{
	BEGIN_READ(buffer, size);

	return 1;
}

int HLCamClient_OnCameraRemovedMessage(const char* name, int size, void* buffer)
{
	BEGIN_READ(buffer, size);

	return 1;
}

namespace Cam
{

}
