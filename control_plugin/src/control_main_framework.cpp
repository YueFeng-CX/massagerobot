/*
 * control_main_framework.cpp
 *
 *  Created on: 2023年6月15日
 *      Author: cx
 */

#include <iostream>

#include <include/control_main_framework.hpp>

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
		/// Configure is called after the system is instantiated and all entities
		/// and components are loaded from the corresponding SDF world, and before
		/// simulation begins exectution.
		std::cout << "configure" << std::endl;
	}

    void MainFrameworkSystem::PreUpdate(const gz::sim::UpdateInfo &_info,
                gz::sim::EntityComponentManager &_ecm)
    {
    	// Apply forces / torques
    	//ignition::gazebo::Joint::SetForce
    	if(not _info.paused)
    		std::cout << "PreUpdate" << std::endl;
    }

    void MainFrameworkSystem::PostUpdate(const gz::sim::UpdateInfo &_info,
                const gz::sim::EntityComponentManager &_ecm)
    {
    	// Get and process data every time step from sensors (robot state)
    	if(not _info.paused)
    		std::cout << "PostUpdate" << std::endl;
    }

    void MainFrameworkSystem::Reset(const gz::sim::UpdateInfo &_info,
                 gz::sim::EntityComponentManager &_ecm)
    {
    	// Called when reset world
    	std::cout << "Reset" << std::endl;
    }

}


