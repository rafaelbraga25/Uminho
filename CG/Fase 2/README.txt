A pasta Engine/build/demos já contém alguns modelos e ficheiros xml.

Modelos:
	box.3d
	boxdiv.3d
	cone.3d
	plane.3d
	sphere.3d

Ficheiros xml:
	box.xml - Carrega o modelo de uma box sem divisões.
	boxdiv.xml - Carrega o modelo de uma box com 4 divisões.
	cone.xml - Carrega o modelo de um cone.
	plane.xml - Carrega o modelo de um plano.
	sphere.xml - Carrega o modelo de uma esfera.
	allmodels.xml - Carrega todos os modelos.
	invalidGroup.xml  - Ficheiro xml com um grupo inválido (possui mais que uma tag do tipo translate).
	invalidModels.xml - Ficheiro que possui um grupo com duas tags do tipo models.
	invalidTranslate.xml - Possui uma tag do tipo translate com um atributo inválido.
	scaledModels.xml - O resultado deste ficheiro consiste na representação de duas esferas com 
	                           diferentes escalas. O ficheiro tenta carregar um modelo chamado ring.3d que
							   não está disponível nesta fase.
	solarSystem.xml - Representa um modelo do sistema solar (sol, planetas e lua da terra).
	
	
Se se executar o programa Engine sem argumentos então o programa irá processar o ficheiro
solarSystem.xml, carregando todos os modelos. Pode-se fornecer como argumento outro ficheiro qualquer,
dando o programa Engine prioridade a esse ficheiro.


Interação com o programa engine:
	
Tecla w - Afasta o modelo 
Tecla a - Desloca o modelo para a esquerda
Tecla s - Aproxima o modelo
Tecla d - Desloca o modelo para a direita
Arrow keys - Roda o modelo em torno do eixo dos xx e dos yy
	
Botão do lado direito do rato - Faz surgir um pequeno menu com opções de desenho do modelo.

Botão do lado esquerdo do rato - Permite mudar a perspetiva da câmara com a movimentação
                                               do rato