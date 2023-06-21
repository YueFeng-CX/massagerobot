/*
 * pid_controller.cpp
 *
 *  Created on: 2023年6月21日
 *      Author: cx
 */

#include <include/pid_controller.hpp>

namespace YF
{
	/// \brief Implement control algorithm here. A control algorithm should fill the joint actuator forces.
    /// This function is called before simulation or real world updates.
    /// Each robot state variable has been processed in parent class JointsController.
    /// Looking up robot state variables in the parent class for details.
    /// [in] Robot state variables: _jointPositions, _jointVelocities
    /// [out] Joint forces: _jointActuatorTorques[i][0] = joint_torque[i], i from 0 to JOINTNUMBER-1
	void PIDController::execControlAlgorithm()
	{
		double target[6] = {0.0, 0.3, 0.7, 1.3, 1.5, 2.0};
		for (int i = 0; i < _numJoints; i++)
		{
			double force = 0;
			/// Simple PD algorithm
			force = kp[i] * (target[i] - _jointPositions[i]) + kd[i] * (0 - _jointVelocities[i]);
			SetJointTorque(i, force);
		}
	}
}

