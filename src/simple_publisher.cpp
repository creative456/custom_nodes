#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"  // Standard String message type

class SimplePublisher : public rclcpp::Node
{
public:
    SimplePublisher()
        : Node("simple_publisher")  // Name the node
    {
        // Create a publisher for the "topic" topic with a queue size of 10
        publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);

        // Create a timer to call the callback function every second
        timer_ = this->create_wall_timer(
            std::chrono::seconds(1),
            std::bind(&SimplePublisher::timer_callback, this));

        RCLCPP_INFO(this->get_logger(), "Publisher node has been started.");
    }

private:
    void timer_callback()
    {
        auto message = std_msgs::msg::String();
        message.data = "Hello, ROS 2!";
        publisher_->publish(message);
        RCLCPP_INFO(this->get_logger(), "Published: '%s'", message.data.c_str());
    }

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);  // Initialize the ROS 2 system
    rclcpp::spin(std::make_shared<SimplePublisher>());  // Run the node
    rclcpp::shutdown();  // Shutdown the ROS 2 system
    return 0;
}

