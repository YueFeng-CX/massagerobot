/*
 * joint_controller.hpp
 *
 *  Created on: 2023年6月20日
 *      Author: cx
 */

#ifndef JOINTCONTROLLER_HPP_
#define JOINTCONTROLLER_HPP_

#include <iostream>
#include <cstring>
#include <vector>
#include <gz/sim.hh>
#include <include/base_controller.hpp>
#include <include/config.hpp>

namespace YF
{
	class JointsController : public BaseController
	{
	  public: JointsController() {}

	  public: virtual ~JointsController() override {}

	  public: void Configure(
              const gz::sim::Entity &_entity,
              const std::shared_ptr<const sdf::Element> &_sdf,
			  gz::sim::EntityComponentManager &_ecm,
			  gz::sim::EventManager &_eventMgr);

	  /// \brief Called before every time step (simulation or real) to execute control command
	  /// this
	  public: virtual void PreUpdate(const gz::sim::UpdateInfo &_info,
              gz::sim::EntityComponentManager &_ecm) override;

	  /// \brief Called after every time step (simulation or real) to update and process observation data,
	  /// e.g. refresh _jointPositions, _jointVelocities.
	  public: virtual void PostUpdate(const gz::sim::UpdateInfo &_info,
              const gz::sim::EntityComponentManager &_ecm) override;

	  /// TODO, different scenarios implementation
	  public: virtual void PreUpdate() {}
	  public: virtual void PostUpdate() {}

	  /// \brief This function is an algorithm implementation, it uses robot states,
	  /// e.g. links and joints' states, to determine joints' forces in every control time step.
	  public: virtual void execControlAlgorithm();

      /// \brief Set a joint torque
	  /// \param[in] index A non-negative number represents joint index
	  /// \param[in] torque Torque applied to the indexed joint
	  protected: void SetJointTorque(uint64_t index, double torque);

	  protected:
		  uint64_t _numJoints = 0;

		  // joint container for Gazebo gz::sim::Joint
		  std::vector<gz::sim::Joint> _jointContainer;

		  /// joint controller command, array for Gazebo gz::sim::Joint::SetFroce()
		  std::vector<double> _jointActuatorTorques[JOINTNUMBER];

		  /// joint positions (e.g. degree or radian)
		  double _jointPositions[JOINTNUMBER];

		  /// joint velocities (e.g. degree or radian per second)
		  double _jointVelocities[JOINTNUMBER];

		  /// joint torques from joint sensors, no use if no joint sensors
		  double _jointTorques[JOINTNUMBER];
	};
}

#endif /* JOINTCONTROLLER_HPP_ */
