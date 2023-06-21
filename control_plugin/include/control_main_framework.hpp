/*
 * control_main_framework.hpp
 *
 *  Created on: 2023年6月15日
 *      Author: cx
 */
#ifndef CONTROL_MAIN_FRAMEWORK_HPP_
#define CONTROL_MAIN_FRAMEWORK_HPP_


#include <gz/plugin/Register.hh>
#include <gz/sim.hh>
#include <include/joint_controller.hpp>

namespace YF
{
  class MainFrameworkSystem:
    // This class is a system.
    public gz::sim::System,
    // This class also implements the ISystemPreUpdate and ISystemPostUpdate interfaces.
	public gz::sim::ISystemConfigure,
    public gz::sim::ISystemPreUpdate,
    public gz::sim::ISystemPostUpdate,
    public gz::sim::ISystemReset
  {
    public: MainFrameworkSystem();

    public: ~MainFrameworkSystem() override;

    /// \brief This function is called after the system is instantiated and all entities
    /// and components are loaded from the corresponding SDF world, and before
    /// simulation begins execution.
    public: virtual void Configure(
                      const gz::sim::Entity &_entity,
                      const std::shared_ptr<const sdf::Element> &_sdf,
					  gz::sim::EntityComponentManager &_ecm,
					  gz::sim::EventManager &_eventMgr) override;

  	/// \brief Apply forces / torques in this function every time step
    public: void PreUpdate(const gz::sim::UpdateInfo &_info,
                gz::sim::EntityComponentManager &_ecm) override;

    /// \brief Get and process data every time step from sensors (robot state)
    public: void PostUpdate(const gz::sim::UpdateInfo &_info,
                const gz::sim::EntityComponentManager &_ecm) override;

    /// \brief This function is called when resets world
    public: void Reset(const gz::sim::UpdateInfo &_info,
                 gz::sim::EntityComponentManager &_ecm) override;

    private:
		std::shared_ptr<JointsController> jointController_sharePtr;
  };
}


// Include a line in your source file for each interface implemented.
GZ_ADD_PLUGIN(
    YF::MainFrameworkSystem,
    gz::sim::System,
	YF::MainFrameworkSystem::ISystemConfigure,
	YF::MainFrameworkSystem::ISystemPreUpdate,
	YF::MainFrameworkSystem::ISystemPostUpdate)

#endif /* CONTROL_MAIN_FRAMEWORK_HPP_ */
