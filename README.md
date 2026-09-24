# Estágio Ray Tracing
## 1/9/2026
Instalação do Cmake, PPM Viewer e LiveShare.
## 2/9/2026
Início dos estudos da implementação de recursos 3d para os cálculos e demonstrações.
## 3/9/2026
Início da implementação dos cálculos relacionados a distância entre objetos, além de cálculos para direção da luz e distância dela mesma para um objeto, além da criação da câmera e do viewport.
## 4/9/2026
Criação de shading básico.
## 8/9/2026
Implementação de Colisões.
## 9/9/2026
Lista para a classe dos objetos com colisão, usamos o #include de memory e vector, para facilitar o trabalho e usar ponteiros inteligentes + vetores que podem mudar seu tamanho.
## 10/9/2026
Implementação de esfera 3d.
## 11/9/2026
Implementação da classe camera e seus métodos e atributos.
## 14/9/2026
Hoje vimos o conceito de antialiasing, pensamos no que fazer para atingir esse resultado, pretendemos usar o modelo mais simples de extender o raio do centro do pixel até a metade do caminho dos quatro pixels vizinhos, representando a cor daquela pequena região da tela.
## 15/9/2026
Hoje terminamos de fazer a função para o anti-aliasing, pegando lugares aleatórios no pixel, vendo as cores e fazendo a média, para colocar nesse pixel, gerando assim uma imagem mais limpa.
## 16/9/2026
Hoje fizemos uma textura básica, refletindo raios de maneira aleatória, se refletir 100%, irá manter a cor, se absorver tudo, será preto, no momento estamos usamos 50% para ter um cor cinza.
## 17/9/2026
Hoje colocamos um limite na profundidade dos raios para a função não continuar até dar stack overflow, também ignoramos raios muito pertos, para tirar esse tanto de bolinha junta com a outra no hora de renderizar.
## 19/9/2026
Hoje fizemos os raios refletirem em uma maneira menos uniforme e mais distantes do ponto normal do objeto.
A diferença é bem sutil mas as sombras estão melhores e ambas as esferas (o chão é uma esfera larga e fina) tem um tom azulado do céu
## 21/9/2026
Hoje vimos que nossa esfera está bem mais escura do que deveria ser, pois mesmo refletindo 50% dos raios, ela ainda n estava na metade das cores (quando se coloca a foto em um aplicativo e pega a cor), então vimos como os programas normalmente esperam que a imagem seja "gamma corrected", como a nossa era em linear space, a transformamos para gamma space, pegando a raiz quadrada do componente linear.
## 22/9/2026
Hoje começamos a fazer a classe de materiais, decidimos optar por fazer uma classe abstrata, que produz um raio que se espalha, iremos primeiro fazer um material de metal, mas ainda temos que terminar a classe abstrata para facilitar a implementação de outros futuros materiais.
## 23/9/2026
Hoje começamos a ver sobre albedo, que seria a "branquice", usado para definir uma reflexão fracionária, ele vai variar com a cor do material (que usaremos futuramente para implementar materiais de vidro) e pode variar com a direção da visão. Escolheremos sempre espalhar.
