Gazebo世界模型构建流程
1.配置模型，向模型中添加传感器
2.Gazebo默认加载插件较少，需要配置为支持sdf模型中所使用的传感器或其它工具，配置文件为gazebo_server.config,也可直接设置世界sdf文件


程序构建
1. 在build目录下运行terminal
2. > cmake ../.
3. make
4. 配置环境变量
    模型文件和世界环境在resources文件夹中，配置GZ_SIM_RESOUCES_PATH

    修改massage_robot.sdf中
   <include>
      <uri>file:///home/cx/GazeboFiles/models/fr5_robotic_arm</uri>
      <name>FR5urdf</name>
      <pose>-0.68934992341712142 -1.2875498838444697 0 0 0 0</pose>
    </include>
    路径file:///home/cx/GazeboFiles/models/fr5_robotic_arm 模型路径，使其能够正确加载机械臂模型

    配置插件位置GZ_SIM_SYSTEM_PLUGIN_PATH使其找到libControlMainFrameworkSystem.so库
5. 运行gz sim massage_robot.sdf
