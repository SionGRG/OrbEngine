#include "OrbE.h"

class SandOrb : public ORB::App
{
public:
	SandOrb() {}
	~SandOrb() {}

};

ORB::App* ORB::CreateApplication()
{
	return new SandOrb();
}