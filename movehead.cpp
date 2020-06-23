#include <iostream>
#include <alproxies/almotionproxy.h>
#include <qi/os.hpp>

int main(int argc, char **argv)
{
  std::string robotIp = "127.0.0.1"; // Conecta ao Robô pelo ip Padrao local 127.0.0.1

  if (argc < 2) {
    std::cerr << "Usage: almotion_angleinterpolation robotIp "
              << "(optional default \"127.0.0.1\")."<< std::endl;
  }
  else {
    robotIp = argv[1];
  }

  AL::ALMotionProxy motion(robotIp); // Cria uma classe motion (como se fosse a classe do NAO),
  // onde o passa o ip padrao para o construtor

  // A partir dessa motion, nos temos as funções da NAOqi que qremos que o robô faça
  motion.setStiffnesses("Head", 1.0f); // Colocando a joint(Head) energizada (stfiness igual a 1)

// Exemplo irá mostrar um movimento de ângulo fixo para uma junta
// OBS: A junta "Head" tem dois tipos de movimento: HeadYaw e HeadPitch
// Nesse exemplo, iremos interpolar o movimento HeadYaw para 1,0 radiano em 2,0 segundos e 
// depois voltar para a posição 0 em 2 seg
  AL::ALValue angleLists; // Declarando minhas variáveis que irei utilizar
  AL::ALValue timeLists;
  AL::ALValue names      = "HeadYaw"; // Nome do meu movimento
  bool isAbsolute = true; 
  angleLists.clear();
  angleLists = AL::ALValue::array(1.0f, 0.0f); // Criando um array para os meus dois angulos que quero
  timeLists.clear();
  timeLists  = AL::ALValue::array(2.0f, 4.0f); // Os dois tempos que quero 
  isAbsolute = true;
  std::cout << "Uma trajetoria para uma junta" << std::endl;
  //Agora vamos interpolar os nossos angulos com o tempo, ou seja:
  //Ele irá fazer com que a cabeça gire até 1 rad em 2 seg e depois
  //fazer com que ela volte para 0 rad no tempo = 4s (2 seg ate 1 rad e mais 2 seg do 1rad até o 0)  
  motion.angleInterpolation(names, angleLists, timeLists, isAbsolute); // Função para interpolar


  // Voltando o stiffness da junta Head para 0
  motion.setStiffnesses("Head", 0.0f);

  return 0;
}