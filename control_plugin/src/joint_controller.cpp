/*
 * joint_controller.cpp
 *
 *  Created on: 2023年6月20日
 *      Author: cx
 */

#include <iostream>
#include <include/joint_controller.hpp>
#include <include/base_controller.hpp>

/// TODO, move configuration parameters to a YAML file
namespace CONFIG
{
	std::string JointName[6] = {"joint1", "joint2", "joint3", "joint4", "joint5", "joint6"};
	uint64_t JointNumber = JOINTNUMBER;
}

namespace YF
{
		void JointsController::Configure(
              const gz::sim::Entity &_entity,
              const std::shared_ptr<const sdf::Element> &_sdf,
			  gz::sim::EntityComponentManager &_ecm,
			  gz::sim::EventManager &_eventMgr)
		{
			_numJoints = CONFIG::JointNumber;
			std::cout << "Joints' entities ID: ";
			for (int i = 0; i < _numJoints; i++)
			{
				auto entity = _ecm.EntityByComponents(gz::sim::components::Name(CONFIG::JointName[i]));
				_jointContainer.push_back(gz::sim::Joint(entity));
				_jointContainer[i].EnablePositionCheck(_ecm, true);
				_jointContainer[i].EnableVelocityCheck(_ecm, true);
				std::cout << entity << " ";
				_jointActuatorTorques[i].push_back(0);
			}
			std::cout << std::endl;
			memset(_jointPositions, 0, sizeof(_jointPositions));
			memset(_jointVelocities, 0, sizeof(_jointPositions));
			memset(_jointTorques, 0, sizeof(_jointPositions));
		}

		void JointsController::PreUpdate(const gz::sim::UpdateInfo &_info,
                gz::sim::EntityComponentManager &_ecm)
		{
			execControlAlgorithm();
			for (int i = 0; i < 6; i++)
			{
				_jointContainer[i].SetForce(_ecm, _jointActuatorTorques[i]);
			}
		}

		///	\brief Other states can be accessed by ECM, for example,
		/// auto parent = _ecm.Component<gz::sim::components::Pose>(_entity); parent->Data();
		void JointsController::PostUpdate(const gz::sim::UpdateInfo &_info,
                const gz::sim::EntityComponentManager &_ecm)
		{
			for(int i = 0; i < _numJoints; i++)
			{
				auto pos = _jointContainer[i].Position(_ecm);
				auto vel = _jointContainer[i].Velocity(_ecm);
				if (!pos or !vel)
				{
					gzerr << "[Function] PostUpdate, joint not exists." << std::endl;
					return;
				}
				_jointPositions[i] = (*pos)[0];
				_jointVelocities[i] = (*vel)[0];
			}

			std::cout << "Joint Positions: " << _jointPositions[0] << ", " << _jointPositions[1]
				      << ", " << _jointPositions[2] << ", " << _jointPositions[3]
					  << ", " << _jointPositions[4]	<< ", " << _jointPositions[5] << std::endl;

			std::cout << "Joint Velocities: " << _jointVelocities[0] << ", " << _jointVelocities[1]
			          << ", " << _jointVelocities[2] << ", " << _jointVelocities[3]
					  << ", " << _jointVelocities[4] << ", " << _jointVelocities[5] << std::endl;

			//gz::sim::components::DepthCamera

		}

		void JointsController::SetJointTorque(uint64_t index, double torque)
		{
			if(index >= _numJoints)
			{
				std::cout << "[Function Error] SetJointTorque(" << index << ", double" << torque << ")"
						<< ", index is out of bound." << std::endl;
				return;
			}
			_jointActuatorTorques[index][0] = torque;
		}

		/// brief Implement control algorithm here
		/// This function should be overridden.
		/// [in] Robot state variables: _jointPositions, _jointVelocities
		/// [out] Joint forces: _jointActuatorTorques[i][0] = joint_torque[i], i from 0 to JOINTNUMBER-1
		void JointsController::execControlAlgorithm()
		{

		}

}


