***Candy Crush - Guilherme Luiz***

Nesse documento iremos seguir a ordem de execução dos métodos.
Sendo cada método tratado individualmente como um tópico.

**main**
Nele estão contidas as *rotinas de inicialização*, que são responsáveis por inicializar as funções do alegro necessárias para a criação do programa. Dentre elas estão inclusas funções resposáveis pelo *IO*, *timer*, *display*, *fonte*, *eventListeners*, *desenho*, dentre outras reposáveis pelo funcionamento básico do programa.

Também está a presente a chamada das funções resposáveis por manter o programa funcionando perfeitamente até que o número de jogadas máximo seja atingido.

E por fim, está presente a parte de verificação de score vs record. E também a tela que exibie se o usuário bateu o recorde ou não.

**draw_candy**
Nesse método é desenhado o doce no tamanho correto de acordo de acordo com o seu tipo.

**initGame**
Nele a matriz é inicializada, sendo preenchida de acordo com a Struct *Candy*, presente no início do arquivo. Além disso, nele é impressa a matriz inicial gerada pelo programa. Vale lembrar que a mtriz é preenchida aleatoriamente, com um número gerado pelo método *generateRandomCandy()*

**generateRandomCandy**
Nesse método é gerado um número aleatório de 1 até quatro, sendo que cada número representa um formato geométrico(ou doces). O valor de cada formato gemétrico é atribuído em um define logo no incício do arquivo.

**processaMatriz** 
No processaMatriz são verificadas as sequências de doces completas e caso alguma seja encontrada, ela deve ser excluída através da chamada do método *clearSequence*. Além disso, também são contabilizados os pontos dado o estado da matriz atual.

**clearSequence**
No clearSequence são excluídas as sequências de doces iguais e contabilizados os pontos de acordo com cada sequência excluida.

**atualizaOffset**
Nesse método a matriz do jogo é modificada a partir do modo que ela se encontra. Caso o elemento não esteja ativo, ele terá seu *type* modificado para 0, tornado assim sua cor igual a preto.

**atualizaMatriz**
No atualizaMatriz a matriz do jogo é atualizada de acordo com o que foi processado até o momento no método *atualizaOffset*. Dessa forma, os elementos da matriz são modificados para que possam ser exluídos pelo *processaMatriz* futuramente. Além disso no final do *atualizaMatriz*, o método *completaMatriz* é chamado para que ele as posições que foram excluídas através da jogada possam ser preenchidas novamente.

**completaMatriz**
Nele é verificado o *type* do elemento da matriz e caso ele seja igual a zero, o elemento será recriado.

**getCell**
Nesse método é feito o cálculo para a descoberta da posição da célula a qual foi solicitada a ação gerada pelo movimento do mouse.

**distancia**
Nesse método é calculada a distância pitagórica entre dois elementos da matriz.

**troca**
No *troca* é feita a troca dos elementos de origem e destino, com o auxílio de uma variável. Além disso o número de jogadas é decrementado e é emitido um som para auxiliar o usuário no entendimento do processo.

**newRecord**
Nesse método é aberto o arquivo recorde.txt, lido o valor dentro do mesmo e verificado se a pontuação atual do jogo é maior do que o recorde previamente escrito no arquivo. Caso seja verdadeiro, é chamado o método *musicaRecorde* e gravado no arquivo o novo recorde.

**musicaRecorde**
Sequência de Beeps e Sleeps para a criação da música que simboliza que o usuário bateu o recorde.
*talvez essa música seja muito familiar*.

***Como Jogar***

Para jogar o Candy Crush, você deve pensar como um jogo de candy crush normal, porém apenas com as regras básicas de negócio, ou seja, as que fazem parte da fundação do jogo.

**Mover Peças** As peças podem ser movidas em qualquer direção, incluindo a diagonal. Porém vale lembrar que é possível trocar apenas peças vizinhas.

**Como Ganhar** Para ganhar o jogo, deve-se fazer a maior quantidade de pontos. Os pontos são feitos a partir da combinação de peças de mesmo formato e cor. Portanto, você deve combinar sequências de peças para fazer pontos. Quanto mais sequências, mais pontos!
