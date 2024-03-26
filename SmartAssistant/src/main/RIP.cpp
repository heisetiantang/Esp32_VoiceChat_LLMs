#include <vector>
#include <iostream>

struct Route
{
    std::string destinationNetwork;
    int distance;
    std::string nextHop;
};

void updateRoutingTable(std::vector<Route> &routingTable, const std::vector<Route> &receivedRoutes, const std::string &sender)
{
    for (const auto &receivedRoute : receivedRoutes)
    {
        Route updatedRoute = {receivedRoute.destinationNetwork, receivedRoute.distance + 1, sender};

        bool isRouteUpdated = false;
        for (auto &route : routingTable)
        {
            if (route.destinationNetwork == updatedRoute.destinationNetwork)
            {
                if (route.nextHop == sender)
                {
                    route.distance = updatedRoute.distance;
                }
                else if (updatedRoute.distance < route.distance)
                {
                    route.distance = updatedRoute.distance;
                    route.nextHop = updatedRoute.nextHop;
                }
                isRouteUpdated = true;
            }
        }

        if (!isRouteUpdated)
        {
            routingTable.push_back(updatedRoute);
        }
    }
}
// 主函数
int main()
{
    // 存储路由表
    /*
    路由表信息是计算机网络中用于确定数据包从发送者到目的地的路径的重要数据。
    它通常由路由器或交换机等网络设备维护和使用。
    路由表信息包括目标网络地址、距离或成本以及下一跳路由器或接口等信息。当数据包到达路由器时，路由器根据路由表信息决定应该将数据包转发到哪个下一跳路由器或接口。
    更新路由表信息是网络中动态路由协议的一个重要功能，它使网络设备能够动态地学习网络拓扑变化并更新路由表，以便维护最佳的数据包转发路径。
     */
    std::vector<Route> routingTable;
    // 接收到的路由表
    std::vector<Route> receivedRoutes = {{"192.168.1.0", 1, "Router_X"}};
    // 更新路由表
    updateRoutingTable(routingTable, receivedRoutes, "Router_X");

    // Display the updated routing table.
    for (const auto &route : routingTable)
    {
        std::cout << "Destination Network: " << route.destinationNetwork
                  << ", Distance: " << route.distance
                  << ", Next Hop: " << route.nextHop << std::endl;
    }

    return 0;
}
