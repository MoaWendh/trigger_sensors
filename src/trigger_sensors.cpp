/****************************************************************************
 Autor: Moacir Wendhasuen 
 Data: 17/01/2022

*****************************************************************************/

#include "ros/ros.h"  // Header para o pacotes do ROS
#include <string>
#include "std_msgs/Float64.h"
#include "std_msgs/String.h" // Headder necesśário para poder publicar msgs.
#include "std_msgs/Bool.h" //Tipo booleano.


class Trigger{
    public:
        Trigger(ros::NodeHandle *nh){
            count=0; // Incializa count quando cria a classe.
            ct_num_triggers=0;
            start=false; // Inicializa o flag start quando cria a classe.

            // Incicializa também como o ponteiro *nh do NodeHandle. 
            // Também registra a Callback triggerCallback() vinculada 
            // ao topico /trigger_tst. Sempre que um novo valor for 
            // publicado em trigger_tst, a callback será executada.
            // trigger_tst= é o topico.
            // 10= é o tamahno tamanho do buffer. 
            // A callback é passada por referência, ponteiro.          
            subs_counter= nh->subscribe("/contador", 10, &Trigger::counterCallback, this);
            subs_trigger= nh->subscribe("/trigger_ins", 10, &Trigger::triggerCallback, this);        
            pub_trigger_stereo= nh->advertise<std_msgs::Bool>()
        
        }

        // Callback que irá ler o Pvalor publicado no tópico /trigger_tst
        // e incrementar o count com este valor.
        void counterCallback(const std_msgs::Float64 &msg){
            count= count + msg.data; //Incrementa com o valor de /trigger_tst
            ROS_INFO("Contagem atual: %f",count); // Publica mensagem

        }

        void triggerCallback(const std_msgs::Bool &msg){
            if (msg.data){
               ++ct_num_triggers; //Incrementa com o valor de /trigger_tst
               ROS_INFO("Trigger numero: %d",ct_num_triggers); // Publica mensagem
            }
            else
               ROS_INFO(" Finalizou o trigger!!"); // Publica mensagem

        }


    private:
        double count;
        bool start;
        int ct_num_triggers;
        ros::Subscriber subs_counter; //Instancia primeiro Subscriber
        ros::Subscriber subs_trigger; //Instancia segundo Subscriber
        ros::Publisher pub_trigger_stereo; 
};        

int main(int argc, char **argv){
    ros::init(argc, argv, "trigger_sensors");
    ros::NodeHandle nh;

    Trigger trigger = Trigger(&nh);
    ros::spin();


    /* ros::Rate loop_rate(1);

    ros::Publisher trigger_pub = nh.advertise < std_msgs::String>("trigger_sensors",1000);


    int count=0;
    std::string msgPadrao= "Trigger dos sensores numero: " ;

    while (ros::ok()){
        std::string msg= msgPadrao + std::to_string(count);

        ROS_INFO("%s", msg.c_str());

        std_msgs::String msg_pub;
        msg_pub.data= msg;

        trigger_pub.publish(msg_pub);
        

        ros::spinOnce();
        loop_rate.sleep();
        count++;
    } */

    return 0;
}