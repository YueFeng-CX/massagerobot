/*
 * control_main_framework.hpp
 *
 *  Created on: 2023年6月15日
 *      Author: cx
 */

#include <gz/plugin/Register.hh>
#include <gz/sim/System.hh>

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

    public: virtual void Configure(
                      const gz::sim::Entity &_entity,
                      const std::shared_ptr<const sdf::Element> &_sdf,
					  gz::sim::EntityComponentManager &_ecm,
					  gz::sim::EventManager &_eventMgr) override;

    public: void PreUpdate(const gz::sim::UpdateInfo &_info,
                gz::sim::EntityComponentManager &_ecm) override;

    public: void PostUpdate(const gz::sim::UpdateInfo &_info,
                const gz::sim::EntityComponentManager &_ecm) override;

    public: void Reset(const gz::sim::UpdateInfo &_info,
                 gz::sim::EntityComponentManager &_ecm) override;
  };
}


// Include a line in your source file for each interface implemented.
GZ_ADD_PLUGIN(
    YF::MainFrameworkSystem,
    gz::sim::System,
	YF::MainFrameworkSystem::ISystemPreUpdate,
	YF::MainFrameworkSystem::ISystemPostUpdate)
