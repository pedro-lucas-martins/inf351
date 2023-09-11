  Para o desenvolvimento dessa etapa do trabalho, foi pensado em utilizar a funcao "delaymicroseconds()" existente para acender e apagar o led
em uma velocidade na qual fosse possivel "emular" uma sensacao de intensidade na luz dos leds.

  Para facilitar a criacao de novas cores, foram criadas funcoes, aplicando o conhecimento aprendido em aula sobre DDR e PortB, tendo em vista tal fato, foram criadas as seguintes cores:
# #VERMELHO:# o led vermelho e aceso e depois de 1000 microsegundos, apagado.
# #VERDE:# o led verde e aceso e depois de 1000 microsegundos, apagado.
# ##AZUL:# o led azul e aceso e depois de 1000 microsegundos, apagado.
# ##ROXO:# O led vermelho acende e apaga a cada 400 microsegundos e o led azul acende e apaga a cada 1000 microsegundos.
# #CIANO:# O LED  azul acende e apaga a cada 400 microsegundos e o led verde acende e apaga a cada 900 microsegundos.
# #LARANJA:# O LED vermelho acende e apaga a cada 1000 microsegundos e o LED verde acende e apaga a cada 200 microsegundos.
# #ROSA:# O LED vermelho acende e apaga a cada 400 microsegundos e o LED azul acende e apaga a cada 200 microsegundos.
# #AMARELO#: O LED vermelho acende e apaga a cada 650 microsegundos e o LED verde acende e apaga a cada 450 microsegundos.

#  A velocidade na qual os LED`s acendem e apagam sao muito rapidas, portanto imperceptiveis, "emulando" a alteracao da intensidade demonstrada pela cor, tornado-se possivel criar diferentes cores
com a mistura das tres primeiras cores criadas.
