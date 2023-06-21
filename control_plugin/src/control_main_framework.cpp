/*
 * control_main_framework.cpp
 *
 *  Created on: 2023年6月15日
 *      Author: cx
 */

#include <iostream>
#include <include/control_main_framework.hpp>
#include <include/pid_controller.hpp>

namespace YF
{
	MainFrameworkSystem::MainFrameworkSystem()
	{}

    MainFrameworkSystem::~MainFrameworkSystem()
    {}

	void MainFrameworkSystem::Configure(const gz::sim::Entity &_entity,
			const std::shared_ptr<const sdf::Element> &_sdf,
			gz::sim::EntityComponentManager &_ecm,
			gz::sim::EventManager &_eventMgr)
	{
		jointController_sharePtr.reset(new PIDController());
		jointController_sharePtr->Configure(_entity, _sdf, _ecm, _eventMgr);
	}

    void MainFrameworkSystem::PreUpdate(const gz::sim::UpdateInfo &_info,
                gz::sim::EntityComponentManager &_ecm)
    {
    	if(not _info.paused)
    	{
    		jointController_sharePtr->PreUpdate(_info, _ecm);
    	}
    }

    void MainFrameworkSystem::PostUpdate(const gz::sim::UpdateInfo &_info,
                const gz::sim::EntityComponentManager &_ecm)
    {

    	if(not _info.paused)
    	{
    		jointController_sharePtr->PostUpdate(_info, _ecm);
    	}
    }

    void MainFrameworkSystem::Reset(const gz::sim::UpdateInfo &_info,
                 gz::sim::EntityComponentManager &_ecm)
    {
    	std::cout << "Reset" << std::endl;
    }

}


