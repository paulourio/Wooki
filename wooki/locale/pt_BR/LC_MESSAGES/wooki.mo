��    w      �  �   �      
     
  .   9
  1   h
  .   �
  *   �
  %   �
  &        A     T     t     �     �  '   �     �     �  A   �     (     H     X  .  i     �     �     �     �     �  /   �     )  /   @  .   p  /   �     �  
   �  H   �  <   A  i   ~  	   �     �       O         p     �     �     �  4   �  �         �     �          $     9     P     h     w  �  �          ,  1   =  .   o     �      �     �  "   �     �  R        d     �     �     �  6   �  �   �  5   �     �  �   �     �     �  �       �     �  I   �  F   :  C   �     �  P   �  0     �  N  
   "  -   %"  /   S"     �"  J   �"     �"  <   �"     (#     ;#  .   Y#  	   �#     �#  '   �#     �#     �#     �#  $   �#     $  	   =$     G$     M$     _$     k$     t$  $   |$  
   �$     �$  	   �$  
   �$     �$     �$     �$     %  �   %  (   '  $   9'  5   ^'  2   �'  '   �'  '   �'  )   (     A(     U(     t(     �(     �(  /   �(     �(     �(  J   �(  $   F)     k)     |)  d  �)     �+     ,     ,     7,  (   K,  ;   t,  '   �,  :   �,  ?   -  <   S-  2   �-     �-  Q   �-  E   .  y   b.     �.  #   �.     /  [   '/     �/     �/     �/      �/  Y   �/  �   F0     1  &   31     Z1     z1     �1     �1     �1     �1  �  �1  !   �3     �3  5   �3  4   
4     ?4  !   D4     f4  ,   �4     �4  ^   �4     15     Q5     e5  %   |5  :   �5  �   �5  I   �6  '   �6  
  7     8  $   $8  �   I8  H  9  !   `:  f   �:  J   �:  I   4;     ~;  X   �;  9   �;  E  <     _B  3   kB  4   �B     �B  M   �B     <C  A   EC     �C  +   �C  <   �C  	   D     D  (   %D     ND     WD     `D  !   sD     �D     �D     �D     �D  
   �D  
   �D     �D  *   �D     E     (E  
   :E     EE     QE     hE     �E     �E     P          i   _   j   n       h              X   `   8   0   a   /          T   L           R       (          H   \   e   K   s   k          7   Q       G   )   f   N      9       u   A      I   +       g      t   >       U      w                 =       :   V              &   J   #             !      p   d   S                 '          O   c              q       %   D       ?      	          1          *   W   v       3       b   <       "   m           5       
   C   ]      $   .   F       r          B       4   Z   ;       o   ,      [              -   6   ^   @   Y       l   M             2   E            	%sChunks not being used%s: %i
 	%sNumber of chunks allocated with mmap%s: %i
 	%sSize of chunks allocated with mmap%s: %i bytes 	%sTop-most releasable chunk size%s: %i bytes
 	%sTotal allocated with malloc%s: %i bytes 	%sTotal bytes allocated%s: %i bytes  	%sTotal memory not in use%s: %i bytes 	New integer @ %p
 	New stack allocated at %s%p%s
 	Read with success: %d
 	Stack freed.
 	Stack is empty
 	Updating object pointer from %p to %p
 
EOF Received
 %s %s%sError%s: operation blocked by safe_working. (object is null)
 %s%sWarning%s: object is null!
 %sClass %s%s%s
 %sMemory Info%s
 %sWooki Interpreter Help%s
	Wooki interpreter is a program to help in analysis of data structures, with tools for benchmarking and debug. The data structures are compiled with the interpreter, and they are connect to the interpreter throught an interface. To see all interfaces (objects), type "print objects"
	To start using an object, first you need to create an object and then commands for the structure can be passed.
How to use help
	Type "help" and the item you want to see about, for instance:
		help new  -- Show help information for "new" command.
 Benchmark Tool
 Bye! Calling parser @ %s%p%s
 Calling user trigger..
 Can't change type to '%s'
 Can't generate random value betweeb this range
 Can't read '%s' as %s
 Can't register object '%s'. It already exists.
 Can't register parser for '%s'. No space left. Can't register trigger for '%s'. No space left. Can't set type. It is fixed.
 Class name Copyright (c) 2011 Chewbacca Software Foundation.
All Rights Reserved.

 Copyright (c) 2011 Paulo Roberto Urio.
All Rights Reserved.
 Create an instance of object. When command new is executed
the command "sel [object]" is implicitly run.
 Data type Data type set to %s%s%s
 Debug level: %s%s%s
 Exit Interpreter
	Exit from interpreter program returning status OK to system.
 Finalizing core..
 Finalizing parser..
 Finalizing runtime..
 Found reference of %p @ %p!
 Garbage Collector
	Invoke Ewoks to free input data.
 Generate a random value.
	Generate a random value and throw to the destination.
	The destination can be a register, a buffer or a opcode
	Example: rnd 10 40 %%eax  -- Random between 10 and 40, store in %%eax
 Generated random value: %d
 Generating random (%d..%d): 
 Ignoring line (too big)
 Initializing core..
 Initializing parser..
 Initializing runtime..
 Items in cache Memory Optimization Memory Optimization
	 If activated, when a new data is going to be pushed to
	a data structure, register or buffer, the interpreter
	will search into already allocated data for same value.
	If found, a reference to this data is passed, avoiding
	 Note: memory optimization must be defined in the very start
	of the program!
	memory duplication.
	Activate: optmem 1
	Deactivate: optmem 0
 Memory optimization: %s%s%s
 Memory: %i bytes Missing name for benchmark. (ex: bm compare a b)
 Missing name for benchmark. (ex: bm save bma)
 Name New object: %s%s%s %s@%s %s%p%s
 No help for %s
 No reference was found. Creating:
 Object %s%s%s not found.
 Object %s%s%s not found. Type "print objects" to get a list of installed objects.
 Object %s%s%s was not found.
 Object found!
 Object information Opcode %s%s%s is not defined.
 Parser registered:
	OP Code: %s%s%s
	Function: %s%p%s
 Print an object.
Available built-in objects:
	objects		List installed objects.
	registers	List interpreter registers values
	ewok		Information about the memory management
 Push values into data structure
	Example: push 1 2 3
 Reached maximum of benchmarks
 Run a loop iteration
	Execute a command, passing values between
	a range, and if defined stepping values.
	Examples:
		for 1 to 5, append          -- Equivalent: append 1 2 3 4 5
		for 2 to 10 step 2, append  -- Equivalent: append 2 4 6 8 10
 Safe working Select an object to work with.
 Set data type to be stored.
	After allocate an object the type is fixed,
	and will not be able to change anymore.
	Example: type int  -- Set data type to integers
 Set debug level.
	Informations about the interpreter and data structs
	are printed to stderr according to level set.
	Example: debug 1  -- Set to basic debug
	0	no debug. Only errors are showed.
	1	basic debug.
	2	extreme debug.
	3	non-sense debug. Not recommended for users.
 Setting debug level to %d.
 Show Memory Analysis
	Use this command to see the program memory status.
 Skipping trigger: number of parameteres do not reach minimum allowed.
 Skipping trigger: number of parameteres ultrapass maximum allowed.
 Syntax There are %d objects. The list bellow show each object
separated by class name.
 There is no selected object for this operation.
 This work is licensed under the Creative Commons Attribution-NonCommercial 3.0 Unported License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/3.0/ or send a letter to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
%sYou are free%s:
	%sto Share%s — to copy, distribute and transmit the work
	%sto Remix%s — to adapt the work
%sUnder the following conditions%s:
	%sAttribution%s — You must attribute the work in the manner 
		specified by the author or licensor (but 
		not in any way that suggests that they endorse 
		you or your use of the work).
	%sNoncommercial%s — You may not use this work for commercial purposes.
%sWith the understanding that%s:
	%sWaiver%s — Any of the above conditions can be waived if you get 
		permission from the copyright holder. 
	%sPublic Domain%s — Where the work or any of its elements is in 
		the public domain under applicable law, that 
		status is in no way affected by the license. 
	%sOther Rights%s — In no way are any of the following rights 
		affected by the license: 
	◉ Your fair dealing or fair use rights, or other applicable
		copyright exceptions and limitations;
	◉ The author's moral rights;
	◉ Rights other persons may have either in the work itself or in 
		how the work is used, such as publicity or 
		privacy rights.
%sNotice%s — This is a human-readable summary of the Legal Code.
	Check out the full license in the web site.
 Time: %lf
 Token '%s' is bigger than allowed. Skipping.
 TokenOverflow: The line has reached the limit.
 Trigger not found.
 Trigger registered (for object %s%s%s)
	OP Code: %s%s%s
	Function: %s%p%s
 Triggers Type "help", "copyright" or "license" for more information.
 Type not defined!
 Warning: can't read integer.
 You must select a object before use commands.
 [boolean] [from] [to] [destination] [from] to [to] (step [step]), [command] [level] [object] [times], [command] accepts from %d until %d parameters
 activate_trigger("%s", %p, %u)
 activated basic currently created deactivated disabled extreme no restriction for parameters count
 non-sense! not created parameter parameters takes %d parameters
 takes at least %d %s
 takes no paramaters
 takes up to %d %s
 Project-Id-Version: Wooki
Report-Msgid-Bugs-To: 
POT-Creation-Date: 2011-04-20 19:12-0300
PO-Revision-Date: 
Last-Translator: Paulo Roberto Urio <paulo@archlinux.us>
Language-Team: Jimmy
Language: 
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
X-Poedit-Language: Portuguese
X-Poedit-Country: BRAZIL
X-Poedit-SourceCharset: utf-8
X-Poedit-KeywordsList: _r;_
X-Poedit-Basepath: .
X-Poedit-SearchPath-0: ../../..
X-Poedit-SearchPath-1: ../../../../stack
 	%sPedaços não sendo utilizados%s: %i
 	%sPedaços alocados com mmap%s: %i
 	%sTamanho dos pedaços alocados com mmap%s: %i bytes 	%sTamanho do pedaço mais liberável%s: %i bytes
 	%sTotal alocado com malloc%s: %i bytes 	%sTotal de bytes alocados%s: %i bytes  	%sTotal de memória liberada%s: %i bytes 	Novo inteiro @ %p
 	Nova pilha alocada em %s%p%s
 	Leitura sucedida: %d
 	A pilha foi liberada.
 	A pilha está vazia
 	Atualizando ponteiro do objeto: de %p para %p
 
EOF Recebido
 %s %s%sErro%s: operação bloqueada pelo safe_working. (o objeto está nulo)
 %s%sAtenção%s: objeto está nulo!
 %sClasse %s%s%s
 %sStatus da Memória%s
 %sAjuda do Interpretador Wooki%s
	Interpretador Wooki é um programa para ajudar na análise de estrutura de dados, com ferramentos para benchmarking e debug. As estruturas de dados são compiladas junto com o interpretador, sendo ligadas através de uma interface. Para ver todas as interfaces (objetos), digite "print objects"
	Para começar a usar um objecto, primeiro você precisa criá-lo, para que então, os comandos digitados possam ser passados para as estruturas.
Como usar a ajuda
	Digite "help" e o termo que você deseja ver, por exemplo:
		help new  -- Mostra informações sobre o comando "new".
 Ferramenta de Benchmark
 Tchau! Chamando analizador @ %s%p%s
 Chamando gatilho..
 Não foi possível mudar tipo para '%s'
 Não foi possível gerar valor aleatório dentro da margem
 Não foi possível ler '%s' como um %s
 Não foi possível registrar objeto '%s'. Ele já existe.
 Não foi possível registrar analizador para '%s'. Sem espaço. Não foi possível registrar gatilho para '%s'. Sem espaço. Não foi possível alterar tipo. Está bloqueado.
 Classe Copyright (c) 2011 Chewbacca Software Foundation.
Todos os direitos reservados.

 Copyright (c) 2011 Paulo Roberto Urio.
Todos os direitos reservados.
 Cria uma instância do objecto. Quando o comando new for executado
o comando "sel [object]" é implicitamente executado.
 Tipo de dados Tipo de dados alterado para %s%s%s
 Nível de debug: %s%s%s
 Sair do Interpretador
	Sair do programa interpretador retornando status OK para o sistema.
 Finalizando núcleo..
 Finalizando analizador..
 Finalizando runtime..
 Referência encontrada! %p @ %p
 Coletor de Lixo
	Invoca Ewoks pra a onerosa tarefa de remover o lixo (dados de entrada).
 Gerar um valor aleatório.
	Gera um valor aleatório e joga para o destino.
	O destino pode ser um registrador, um buffer ou um comando
	Exemplo: rnd 10 40 %%eax  -- Valor entre 10 e 40, armazena em %%eax
 Número aleatório gerado: %d
 Gerando número aleatório (%d..%d): 
 Ignorando linha (muito grande)
 Inicializando núcleo..
 Inicializando analizador..
 Inicializando runtime..
 Itens em cache Otimização da memória Otimização da Memória
	 Se ativada, quando um novo dado entrar no programa
	para uma estrutura de dados, registrador ou buffer, o interpretador
	irá buscar pelo mesmo valor nos dados que já entraram no programa.
	Se encontrado, uma referencia para esse dado é passado, evitando
	duplicação de dados.
	 Nota: otimização de memória precisa ser definida bem no início
	do programa!
	Ativar: optmem 1
	Desativar: optmem 0
 Otimização da memória: %s%s%s
 Memória: %i bytes Faltando nome para o benchmark. (ex: bm compare a b)
 Faltando o nome para o benchmark. (ex: bm save bma)
 Nome Novo objeto: %s%s%s %s@%s %s%p%s
 Ajuda não encontrada para %s
 Nenhum referência foi encontrada. Criando:
 Objeto %s%s%s não encontrado.
 Objeto %s%s%s não encontrado. Digite "print objects" para ver a lista de objetos instalados.
 Objeto %s%s%s não encontrado.
 Objeto encontrado!
 Informação do Objeto O opcode %s%s%s não está definido.
 Analizador registrado:
	OP Code: %s%s%s
	Função: %s%p%s
 Imprime um objeto.
Objetos do interpretador:
	objects		Lista os objetos instalados.
	registers	Lista os registradores do interpretador
	ewok		Informação sobre o gerenciamento de memória
 Executar PUSH dos valores para a estrutura de dados
	Exemplo: push 1 2 3
 Número máximo de benchmarks atingido
 Executar iterações
	Executa um comando, passando os valores dentro de
	uma margem de valores, e se definido, pulando valores.
	Exemplos:
		for 1 to 5, append          -- Equivalente: append 1 2 3 4 5
		for 2 to 10 step 2, append  -- Equivalente: append 2 4 6 8 10
 Modo seguro Seleciona um objeto para trabalhar.
 Definir tipo de dados para serem armazenados.
	Depois de criar um objeto, o tipo de dados é fixado,
	não permitindo alterações posteriormente.
	Exemplo: type int  -- Muda o tipo de dados para inteiros
 Definir o nível de debug.
	Informações sobre o interpretador e o objeto
	são imprimidas em stderr de acordo com o nível definido.
	Exemplo: debug 1  -- Define o debug para o nível básico
	0	sem debug. Apenas erros são mostrados.
	1	debug básico.
	2	debug extremo.
	3	debug sem-noção. Não recomendado para usuários.
 Mudando nível de debug para %d.
 Mostrar Análise da Memória
	Use este comando para ver informações atuais da memória do programa.
 Pulando gatilho: número de parâmetros não atingem o mínimo permitido.
 Pulando gatilho: número de parâmetros ultrapassam o máximo permitido.
 Sintaxe Há %d objetos. A lista abaixo mostra cada objeto
organizado pelas classes dos objetos.
 Não há nenhum objeto selecionado para esta operação.
 A presente obra encontra-se licenciada sob a licença Creative Commons Attribution-NonCommercial 3.0 Brazil. Para visualizar uma cópia da licença, visite http://creativecommons.org/licenses/by-nc/3.0/br/ ou mande uma carta para: Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
%sVocê tem a liberdade de%s:
	%sCompartilhar%s — copiar, distribuir e transmitir a obra.
	%sRemixar%s — criar obras derivadas.
%sSob as seguintes condições%s:
	%sAtribuição%s — Você deve creditar a obra da forma especificada 
		pelo autor ou licenciante (mas não de maneira 
		que sugira que estes concedem qualquer aval a 
		você ou ao seu uso da obra).
	%sUso não-comercial%s — Você não pode usar esta obra para fins comerciais.
%sFicando claro que%s:
	%sRenúncia%s — Qualquer das condições acima pode ser renunciada 
		se você obtiver permissão do titular dos direitos autorais.
	%sDomínio Público%s — Onde a obra ou qualquer de seus elementos estiver em 
		domínio público sob o direito aplicável, esta 
		condição não é, de maneira alguma, afetada pela licença.
	%sOutros Direitos%s — Os seguintes direitos não são, de maneira alguma,  
		afetados pela licença: 
	◉ Limitações e exceções aos direitos autorais ou quaisquer
		usos livres aplicáveis;
	◉ Os direitos morais do autor;
	◉ Direitos que outras pessoas podem ter sobre a obra ou sobre 
		a utilização da obra, tais como direitos de 
		imagem ou privacidade.
%sAviso%s — Este é um resumo amigável da Licença Jurídica.
	Veja a licença integralmente na internet.
 Tempo: %lf
 Símbolo '%s' é maior que o permitido. Ignorando.
 TokenOverflow: A linha atingiu o limite de tamanho.
 Gatilho não encontrado.
 Gatilho registrado (para o objeto %s%s%s)
	OP Code: %s%s%s
	Função: %s%p%s
 Gatilhos Digite "help", "copyright" ou "license" para mais informações.
 Tipo não definido!
 Atenção: não foi possível ler inteiro.
 Você deve selecionar um objeto antes de executar comandos.
 [lógico] [de] [até] [destino] [de] to [até] (step [pular]), [comando] [nível] [objeto] [vezes], [comando] aceita de %d até %d parâmetros
 activate_trigger("%s", %p, %u)
 ativado básico está criado desativado desativado extremo sem restrição no número de parâmetros
 sem-noção! não está criado parâmetro parâmetros aceita %d parâmetros
 precisa de pelo menos %d %s
 não aceita parâmetros
 aceita até %d %s
 