# **João Pedro Rodrigues**

# Sistemas Operacionais

## 3. Processos
**Processo**: um programa em execução, que representa uma unidade de trabalho no sistema operacional.\
**Sistema**: conjunto de processos, alguns executando código do usuário, outros executando código do sistema operacional.

### 3.1 Conceito de processo

#### 3.1.1 O processo

**Componentes de um processo**: código, dados (variáveis globais), pilha (armazenamento temporário de dados ao chamar um função), heap (armazenamento dinâmico de dados).

    Código e dados são fixos, mas pilha e heap podem crescer e diminuir.
    Stack cresce para baixo, heap cresce para cima.

**Programa**: arquivo armazenado em disco contendo uma lista de instruções.

    Um programa se torna um processo quando um arquivo executável é carregado na memória.

#### 3.1.2 Estado do processo

**New**: processo está sendo criado.\
**Running**: instruções estão sendo executadas.\
**Waiting**: processo está esperando por um evento externo (IO, signal).\
**Ready**: processo está pronto para ser atribuido a um processador.\
**Terminated**: processo terminou sua execução.

    Apenas um processo pode estar em running em cada núcleo por vez.

#### 3.1.3 Bloco de controle do processo

Cada processo é representado por um PCB (Process Control Block) no SO.

    O PCB contém informações sobre o processo, como: estado, program counter, registradores, prioridade, gerenciamento de memória, estado IO, infos de cada thread etc.

### 3.2 Escalonamento de processos
**I/O-bound process**: processo em que a maior parte do tempo é gasto em operações de entrada e saída.\
**CPU-bound process**: processo em que a maior parte do tempo é gasto em operações de CPU.

#### 3.2.1 Scheduling Queues
**Ready queue**: fila de processos prontos para serem executados.\
**Wait queue**: fila de processos que estão esperando por um evento externo.

Uma vez despachado para execução, o processo pode:

    1. Terminar sua execução (removido das filas e desalocado os recursos e PCB)
    2. Esperar por um evento externo (wait queue)
    3. Criar um processo filho e ser colocado na wait queue até o filho terminar a execução
    4. Ser removido do core e colocado na ready queue (interrupção ou tempo de execução excedido)

#### 3.2.2 CPU Scheduling
Em alguns SOs pode acontecer swapping: remover um processo da memória e colocar no disco caso não haja memória suficiente para executar um processo.

#### 3.2.3 Troca de contexto
**Contexto**: é representado no PCB do processo. Inclui o valor dos registradores, o estado do processo, as informações de gerenciamento de memória

    Trocar o core do processador para outro processo necessita de state save do processo atual e state restore do processo que será executado.

    Sistema não trabalha durante o switching.

### 3.3 Operações nos processos
O SO identifica o processo pelo PID (Process IDentifier), normalmente um integer.

    Um processo filho pode obter recursos do processo pai ou do SO

Quando um processo criar novos processos, pode acontecer:
    
    1. O pai executa concorrentemente com o filho
    2. O pai espera pelo filho
    
Quanto ao espaço de endereçamento:
    
    1. O filho é uma cópia do pai
    2. O filho tem um novo programa carregado

O pid do processo filho é zero.

Um filho não pode existir sem um pai (órfão).

**zombie process**: processo terminou, mas o pai não chamou pelo wait().

### 3.4 Comunicação entre processos (IPC)
**Independente**: processo que não compartilha memória com outros processos.\
**Cooperativo**: processo que compartilha memória com outros processos.

    Shared memory: uma região de memória compartilhada entre os processos é estabelecida.
    Message passing: os processos trocam mensagens.

Shared memory pode ser mais rápido.\
Message passing utiliza syscalls, então é mais lento.

### 3.6 IPC in message-passing
#### 3.6.1 Naming
Processos que querem se comunicar devem ter um forma de se referenciar ao outro.

    Direct communication: deve haver um link entre os processos.
    Indirect communication: messages são enviadas ou rebecidas por mailboxes ou portas. Mailbox tem identificação única.

#### 3.6.2 Synchronization
Blocking ou nonblocking.

#### 3.6.3 Buffering
Mensagens trocadas são armazenadas em filas temporárias.

    Zero capacity: uma mensagem é enviada, podendo ser novamente enviada apenas quando for recebida.
    Bounded capacity: n mensagens são armazenadas até que o receptor esteja pronto para recebê-las.
    Unbounded capacity: não há limites de mensagens armazenadas.

## 4. Threads e Concorrência

### 4.1 Overview

**Thread**: unidade básica de uso de CPU. Possui um thread ID, um PC, um conjunto de registradores e uma stack. Compartilha com outras threads do mesmo processo a seção de código, data e outros recursos do SO.

    Um processo comum é um processo com uma única thread.

É mais eficiente um processo com múltiplas threads, pois criar um processo é mais custoso que criar uma thread.

Vantagens do multithreading:
    
        1. Responsividade
        2. Compartilhamento de recursos: código, dados e arquivos.
        3. Economia de recursos: criar uma thread é mais rápido e menos custoso que um processo. Troca de contexto é mais rápida.
        4. Escalabilidade: threads podem rodas em paralelo.

### 4.2 Multicore Programming
**Concorrência**: permite que mais de uma tarefa faça progresso.\
**Paralelismo**: permite a execução de mais de uma tarefa ao mesmo tempo.

#### 4.2.2 Tipos de paralelismo
**Data parallelism**: distribuir subconjuntos do mesmo dado entre núcleos, executando a mesma operação.\
**Task parallelism**: distribuir tarefas entre núcleos, executando diferentes operações.

### 4.3 Modelos multithreading
**User threads**: são suportadas acima do kernel e gerenciadas sem ele.\
**Kernel threads**: são suportadas e gerenciadas pelo SO.

#### 4.3.1 Many-to-one
Muitas user-level threads são mapeadas para uma única kernel thread.\
**Vantagem**: é eficiente, pois o gerenciamento da thread é feito pela lib no user-level.\
**Problema**: todo o processo será bloqueado quando uma thread for bloqueada.

#### 4.3.2 One-to-one
Uma user-level thread é mapeada para uma única kernel thread.\
**Vantagem**: maior concorrência, permite paralelismo.\
**Problema**: quanto mais kernel threads, pior a performance do sistema.

#### 4.3.3 Many-to-many
n user-level threads são mapeadas para n ou menos kernel threads.\
**Problema**: difícil de implementar.

## 5. CPU Scheduling
### 5.1 Conceitos
#### 5.1.1 CPU-I/O Burst Cycle
**CPU burst**: tempo que o processo fica executando no CPU.\
**I/O burst**: tempo que o processo fica esperando por um I/O.\
Os processos alternam entre esse dois estados.

#### 5.1.2 CPU Scheduler
Seleciona um processo da ready queue para executar e aloca a CPU para ele.\
A queue é normalmente composta pelos PCBs dos processos.

#### 5.1.3 Preemptive and Nonpreemptive Scheduling
**Preemptive**: o processo pode ser interrompido a qualquer momento.\
**Nonpreemptive**: o processo permanece na CPU até terminar ou o estado ser alterado para waiting.

Race condition pode ocorrer em preemptive scheduling quando dados são compartilhados entre vários processos.

#### 5.1.4 Dispatcher
É o módulo que transfere o controle da CPU de um processo para outro.\
Precisa ser o mais rápido possível, pois é chamado durante a troca de contexto.\
**Dispatcher latency**: tempo entre parar um processo e iniciar outro.

### 5.2 Scheduling Criteria

    1. CPU utilization: quanto mais tempo a CPU estiver ocupada, melhor.
    2. Throughput: número de processos que terminam por unidade de tempo.
    3. Turnaround time: soma do tempo de espera, tempo de execução e tempo de I/O.
    4. Waiting time: tempo que um processo fica esperando na ready queue.
    5. Response time: tempo que o processo leva para começar a executar após ser iniciado.

Desejável:
    
        1. CPU utilization: máximo
        2. Throughput: máximo
        3. Turnaround time: mínimo
        4. Waiting time: mínimo
        5. Response time: mínimo

### 5.3 Scheduling Algorithms
#### 5.3.1 First-Come, First-Served (FCFS)
FIFO queue.\
É não preemptivo.\
**Vantagem**: é simples de implementar.\
**Desvantagem**: tempo médio esperando na fila é geralmente bem grande.

#### 5.3.2 Shortest-Job-First (SJF)
Processos são executados na ordem de menor duração do CPU burst.\
Se dois processos tem o mesmo tamanho de CPU burst, o que chegou primeiro é executado primeiro.\
**Vantagem**: é comprovadamente ótimo.\
**Desvantagem**: não há como implementar, pois não é possível saber o tamanho do CPU burst.\
É possível implementar com estimativas de CPU burst.\
Pode ser preemptivo ou não.

#### 5.3.3 Round-Robin
Define-se um quantum de tempo.\
A ready queue é tratada como uma lista cirular.\
O CPU scheduler percorre a ready queue, executando cada processo por um quantum de tempo.\
Novos processos são adicionados no final da lista.\
Se o processo for finalizado, saí da lista, se não, vai para o fim da lista.\
**Desvantagem**: tempo médio na waiting queue é geralmente bem grande.\
É preemptivo.\
Se o quantum for muito pequeno, o overhead de troca de contexto pode ser maior que o tempo de execução do processo. Se for muito grande, se transforma em FCFS.

#### 5.3.4 Priority Scheduling
A cada processo é atribuído um valor de prioridade.\
A CPU é alocada ao processo com maior prioridade.\
Se possuir dois processos com a mesma prioridade, aplica-se FCFS.\
A prioridade por ser definida:

    1. Internamente: limite de tempo, memória utilizada, etc.
    2. Externamente: definido fora do SO.

**Problema**: starvation.\
**Solução**: aging, aumentar a prioridade de um processo que está esperando há muito tempo.\
Pode ser usado round-robin entre processos de mesma prioridade para evitar starvation.

#### 5.3.5 Multilevel Queue Scheduling
Cria-se uma fila para cada nível de prioridade.

#### 5.3.6 Multilevel Feedback Queue Scheduling
Permite que um processo mude de fila.\
A ideia é separar os processos de acordo com o CPU burst.\
Processos com CPU burst pequeno ficam em uma fila de alta prioridade, e processos com CPU burst grande ficam em uma fila de baixa prioridade.\
Um processo que fica muito tempo na fila de baixa prioridade é movido para a fila de alta prioridade para evitar starvation.\
**Problema**: algoritmo mais complexo.

### 5.4 Thread Scheduling
Kernel level threads que são escalonados pelo SO.\
User level threads são mapeadas para kernel level threads.

### 5.5 Multiprocessor Scheduling
#### 5.5.1 Abordagens para Multiple-Processor Scheduling
**1. Symmetric Multiprocessing (SMP)**: cada processador é auto-esclonável.\
**2. Asymmetric Multiprocessing**: apenas um processador acessa as estruturas de dados do sistema, o master server.

    Abordagem mais comum: cada processador tem sua própria fila de ready queue.

#### 5.5.2 Multicore Processors
Muitos núcleos no mesmo chip.\
Duas ou mais threads em cada núcleo.\
**Hyperthreading**: múltiplas threads em cada núcleo.\
Cada núcleo executa apenas um thread por vez.

#### 5.5.3 Load Balancing
**Load balancing**: distribuir o trabalho entre os processadores. É necessário quando cada processador tem sua própria fila de ready queue.\
**Push migration**: uma tarefa especifica checa periodicamente a carga de cada processador, distribuindo o trabalho entre eles.\
**Pull migration**: um processador idle puxa uma waiting task de um processador ocupado.

#### 5.5.4 Processor Affinity
**Processor affinity**: um processo tem afinidade pelo processador que o está executando (warm cache).\
**Soft affinity**: o SO tem uma política de manter o processo rodando no mesmo processador.\
**Hard affinity**: syscalls especificam o conjunto de processadores que o processo pode ser executado.

#### 5.5.5 Heterogeneous Multiprocessing
**Heterogeneous Multiprocessing**: processadores de diferentes tipos (clock speed, power management).\
**big.LITTLE**: processadores de alta performance são combinados com processadores eficientes em energia.

## 6. Synchronization tools
**Race condition**: diferentes processos acessam e manipulam o mesmo dado concorrentemente, sendo a saída dependente da ordem de execução.

### 6.2 The Critical-Section Problem
**Critical section**: região do código que acessa dados compartilhados.

Uma solução deve satisfazer:
    
        1. Mutual exclusion: apenas um processo pode executar na região crítica por vez.
        2. Progress: se um processo quer entrar na critical section, ele deve eventualmente conseguir.
        3. Bounded waiting: limite de vezes que um processo pode acessar a região crítica, estando outro processo querendo acessá-la também.

Duas abordagens são utilizadas para lidar com região crítica no SO:

    1. Preemptive Kernel: permite um processo ser interrompido enquanto estiver executando no modo kernel.
    2. Non-preemptive Kernel: não permite que um processo seja interrompido enquanto estiver executando no modo kernel.

Preemptive Kernel é mais adequado para real-time systems.

### 6.5 Mutex Locks
Garantir exclusão mútua.\
Proteger a região crítica, evitando race conditions.\
Possui valor booleano, que indica se o lock está disponível ou não.\
As funções devem executar atomicamente, sendo elas:

        acquire(): se o lock estiver disponível, o processo o obtém, caso contrário, o processo é bloqueado.
        release(): libera o lock.

**Vantagem**: não realiza troca de contexto.\
**Desvantagem**: busy waiting, ou seja, o processo fica em loop verificando se o lock está disponível, desperdiçando ciclos de CPU (spin lock).

### 6.6 Semaphores
Variável inteira que é acessada pelas operações wait e signal, que devem ser atômicas.\
Possui um número fixo de recursos disponíveis.\
**wait()**: acessar região crítica - decrementa o valor do semáforo.\
**signal()**: sair da região crítica - incrementa o valor do semáforo.

Pode não haver busy waiting, pois o processo pode ser posto em sleep() até que o semáforo esteja disponível.
### 6.8 Liveness
Conjunto de propriedades que um sistema deve satisfazer para garantir que os processos façam progresso durante o ciclo de vida de execução deles.\
**Liveness failure**: performance e responsividade do sistema são afetados.

#### 6.8.1 Deadlock
#### 6.8.2 Priority Inversion
Processo de alta prioridade bloqueado por um processo de baixa prioridade.

### 6.9 Evaluation

## 7. Synchronization Examples
### 7.1 Classic Problems of Synchronization
#### 7.1.1 Bounded-Buffer Problem
Problema de sincronização entre produtor e consumidor.\
Produtor: pode produzir full buffers (lotação máxima).

#### 7.1.2 Readers-Writers Problem
Problema de sincronização entre leitores e escritores.\
Leitores: podem ler dados compartilhados.\
Escritores: têm acesso exclusivo aos dados compartilhados, ou seja, não pode ser feita leitura enquanto estiver escrevendo.

Se há um escritor esperando, nenhum leitor pode ler.

#### 7.1.3 Dining Philosophers Problem
Problema de sincronização entre filósofos.

### 7.2 Synchronization within the kernel
#### 7.2.2 Linux
Kernel é completamente preemptivo.\
A técnica mais simples de sincronização é o atomic integer.

### 7.3 POSIX Synchronization
User level
#### 7.3.1 POSIX Mutex Locks
#### 7.3.2 POSIX Semaphores

### 7.5 Alternative Approaches
#### 7.5.1 Transactional Memory
Sequência de operações de escrita e leitura em memória realizadas atomicamente.\
Se uma operação falhar, todas as operações anteriores são desfeitas.\
Não é possível deadlock.

#### 7.5.2 OpenMP
Pragma para paralelização de código.

#### 7.5.3 Functional Programming Languages

## 8. Deadlocks
**Deadlock**: situação em que dois ou mais processos estão esperando por um recurso que está sendo utilizado por outro processo, e nenhum deles pode continuar sua execução.

### 8.1 System Model

Uma thread utiliza um recurso da seguinte forma:
    
    1. Solicita o recurso, se não estiver disponível, espera até estar.
    2. Utiliza o recurso.
    3. Libera o recurso.

### 8.2 Deadlock in Multithreaded Applications
#### 8.2.1 Livelock
Ocorre quando dois ou mais processos estão executando, mas nenhum deles está fazendo progresso.\
Occore quando as threads estão em loop, tentando obter o recurso, mas não conseguindo.

### 8.3 Deadlock Characterization
#### 8.3.1 Condições necessárias

        1. Mutual exclusion: pelo menos um recurso deve ser exclusivo (não pode ser compartilhado).
        2. Hold and wait: uma thread deve estar segurando pelo menos um recurso e esperando por outro recurso que está sendo utilizado por outras threads.
        3. No preemption: os recursos não podem ser retirados de uma thread que está esperando por eles.
        4. Circular wait: existe um ciclo de espera entre as threads.

#### 8.3.2 Resource Allocation Graph
Se não há ciclo(s), não há deadlock.\
Se há ciclo(s), **pode haver** deadlock.

### 8.4 Methods for handling deadlocks
Os SOs normalmente assumem que não existe deadlock, ficando a cargo do programador evitar que isso ocorra.\
**Deadlock avoidance**: requer que o SO saiba antecipadamente quais recursos serão utilizados por cada thread.\
**Deadlock prevention**: fornece um conjunto de métodos para garantir que pelo menos uma condição necessária para o deadlock não seja satisfeita.

## 9. Main memory
### 9.1 Background
#### 9.1.1 Basic Hardware
As instruções e dados devem estar na memória principal para a CPU poder executar.\
Em caso de memory stall, um nucleo multithread pode mudar a thread que está em execução.\
Cada processo possui seu próprio espaço de endereçamento:
    
        1. Base register: armazena o endereço base do processo (menor valor).
        2. Limit register: armazena o tamanho do processo.

Se um processo tentar acessar um endereço que não pertence a ele, ocorre um trap que dispara fatal error.

#### 9.1.2 Address Binding
**Address binding**: processo de associar um endereço virtual a um endereço físico.\
Pode ser feito em:
        
        1. Compile time: Sabe-se o endereço em tempo de compilação, código absoluto é gerado, mesmo endereço físico e lógico.
        2. Load time: Não se sabe o endereço em tempo de compilação, código relocável é gerado, mesmo endereço físico e lógico.
        3. Execution time: O processo pode ser movido para outro endereço físico, endereço físico e virtual diferentes.

#### 9.1.3 Logical Versus Physical Address Space
**Logical address**: endereço gerado pela CPU.\
**Virtual address**: endereço lógico gerado em tempo de execução.\
**Memory-management unit (MMU)**: hardware responsável por traduzir endereços lógicos em endereços físicos.\
**Relocation register**: base register.

#### 9.1.4 Dynamic Loading
**Dynamic loading**: as rotinas do código não são carregadas na memória principal até que sejam necessárias.\
**Vantagem**: economia de memória.

#### 9.1.5 Dynamic Linking and Shared Libraries
**Dynamically linked libraries(DLLs)**: bibliotecas compartilhadas que podem ser utilizadas por vários processos.

### 9.2 Contiguous Allocation
Memória possui **duas partições**: uma para o SO (high memory) e outra para os user-processes.\
**Contiguous allocation**: cada processo é alocado em uma região de memória que é contínua com o próximo processo.
#### 9.2.1 Memory Protection
**Memory protection**: cada processo possui seu próprio espaço de endereçamento, o SO pode protege o espaço de endereçamento de um processo para que ele não possa acessar o espaço de endereçamento de outro processo (relocation-register).

#### 9.2.2 Memory Allocation
**Variable-partition**: dá a um processo uma partição de tamanho fixo(varia de acordo com o tamanho do processo). O SO mantém uma tabela que indica quais partições estão livres e quais estão ocupadas.\
**Hole**: espaço livre na memória.\
Se o hole é muito grande, é dividido em duas partes.\
Holes adjacentes são combinados em um único hole.

    First-fit (mais rápido): aloca o processo na primeira partição que couber.
    Best-fit: aloca o processo na partição que tiver o menor tamanho que caiba.
    Worst-fit: aloca o processo na partição que tiver o maior tamanho que caiba.

#### 9.2.3 Fragmentation
**External fragmentation**: espaço livre na memória principal que não pode ser utilizado por nenhum processo (muitos holes pequenos).\
**Internal fragmentation**: em alocações de blocos de tamanho fixo, o espaço utilizado por um processo pode ser menor que o tamanho do bloco alocado, sobrando espaço livre no bloco atribuido ao processo.\
**Solucões para fragmentação externa**: compaction (shuffle, sobrando um grande hole) ou paging.

### 9.3 Paging
Permite que o endereço físico do processo não seja continuo, evita fragmentação externa.\
É implementado com a cooperação do SO e do hardware.
#### 9.3.1 Basic Method
Quebra a memória física em blocos de tamanho fixo (**frames**) e a memória lógica em blocos de mesmo tamanho (**pages**).\
Endereço físico fica completamente separado do endereço lógico.\
Cada endereço gerado pela CPU contém dois campos: **page number** (index para acessar a tabela de páginas) e **offset** (posição dentro do frame).\
**Page table**: tabela que mapeia cada página do processo para um frame da memória física.\
**Não** há fragmentação externa, e pode haver interna.\
O SO mantém uma cópia da tabela de páginas para cada processo.\
**Problema**: aumenta o tempo de context-switch

#### 9.3.2 Hardware Support
Um ponteiro para a tabela de páginas é armazenado no PCB de cada processo.\
Page table é mantida na memória principal.\
**Page-table base register (PTBR)**: aponta para a tabela de páginas.

##### 9.3.2.1 Translation Lookaside Buffer (TLB)
**TLB**: cache de páginas (key, value).\
CPU gera um endereço lógico, TLB procura a página na tabela de páginas, se não encontrar (TLB miss), TLB procura na tabela de páginas do SO.\
Se der miss, armazena a página na TLB.\
Diminui o acesso à memória principal (1 acesso em vez de 2).

#### 9.3.3 Protection
**Page protection**: cada página tem seus bits de proteção na própria tabela (read-write, read-only, valid-invalid, etc).

#### 9.3.4 Shared Pages
**Shared pages**: páginas que podem ser compartilhadas por vários processos.\
Para ser compartilha, o código deve ser reentrante (natureza read-only).

### 9.4 Structure of the Page Table
#### 9.4.1 Hierarchical Paging
Divide a tabela de página em camadas (2-level, 3-level, ...).

#### 9.4.2 Hashed Page Tables
Tabela de páginas é uma tabela hash, onde o número da página virtual é a chave.
Cada valor da tebela é uma lista encadeada (lida com colisões).

#### 9.4.3 Inverted Page Tables
Entrada é um par (pid, page number), realiza-se uma busca na página, se encontrar o par, retorna o número da posição do par na tabela.

### 9.5 Swapping
**Swapping**: quando um processo não cabe na memória principal, parte dele é colocado no disco.

#### 9.5.1 Standard Swapping
**Standard swapping**: mover todo o processo entre a memória principal e o disco.

#### 9.5.2 Swapping with Paging
**Swapping with paging**: páginas de um processo podem ser movidas entre a memória principal e o disco, em vez de todo o processo.

## 10. Virtual Memory
Permite a execução de um processo que não está totalmente na memória principal.

### 10.1 Background
**Vantagens**: quantidade de memória disponível deixa de ser um problema, mais programas podem rodar ao mesmo tempo, menos I/O para load ou swap.
Disponibiliza uma quantidade maior de memória virtual do que a física.\
O espaço de endereçamento virtual de um processo refere-se a visão lógica (ou virtual) de como um processo é armazenado na memória.\
Processos podem compartilhar memória virtual.

### 10.2 Demand Paging
**Demand paging**: páginas são carregadas na memória principal apenas quando são necessárias durante a execução do programa.

#### 10.2.1 Basic Concepts
Valid-invalid bit: indica se a página está na memória principal ou não.\
Se o programa tentar acessar uma página inválida, ocorre um page fault.\
Procedimento quando ocorre um page fault:

        1. Checa-se a internal page table para ver se a referência é válida ou não.
        2. Se não for, encerra o processo. Se for e a página não estiver sido trazida ainda, traz-se ela.
        3. Acha-se um frame livre.
        4. Escalona-se uma operação em disco para lê-la.
        5. Ao se ler, atualiza-se a page table.
        6. Reinicia a instrução que foi interrompida pelo trap.

**Pure demand paging**: nunca traz uma página até que seja necessária.

#### 10.2.2 Free-Frame List
O SO mantém uma lista com frames livres (zerados, segurança) para tratar page faults.

#### 10.2.3 Performance of Demand Paging
Afeta diretamenta a performance do sistema.\
Ideal: **minimizar o número de page faults**.\
Como: trazer as páginas para o espaço de swap.

### 10.3 Copy-on-Write
Permite aos processos pai e filho compartilhar as mesma páginas inicialmente. Essas páginas são marcada como copy-on-write, ou seja, se qualquer processo escrever nelas, uma cópia deve ser feita.

### 10.4 Page Replacement
#### 10.4.1 Basic Page Replacement
Se nenhum frame está livre, encontra-se um que não está em uso e o libera. Para liberar, basta carregar o conteúdo dele no swap space e alterar as tabelas para indicar que não está mais na memória principal.\
*Se nenhum frame está livre, faz-se duas operações: **page-out** e **page-in***.\
*Para reduzir o overhead, utiliza-se o dirty bit.*

#### 10.4.2 FIFO Page Replacement
A página mais antiga é substituída.\
**Problema**: páginas antigas que são muito usadas podem ser substituídas.

#### 10.4.3 Optimal Page Replacement
Substitui a página que não será usada por um longo tempo.\
**Problema**: requer um conhecimento futuro.

#### 10.4.4 LRU Page Replacement
É uma aproximação do optimal page replacement.\
Substitui a página menos recentemente usada.\
Utiliza um conhecimento passado.\
**Problema**: requer hardware assistance (custosa): counters ou stack(se foi usada, remove e poe no topo, assim a LRU fica na base).

#### 10.4.5 LRU-Approximation Page Replacement
Pode-se saber quais paginas foram ou não utilizadas pelo reference bit.\
**Shifting**: desloca-se os bits utilizados em cada intervalo de tempo, LRU será o menor valor.\
**Second chance**: se o reference bit for 1, muda pra 0, se for 0, substitui. Percorre de forma circular.\
**Ordered pair (reference, modify)**: melhor remoção é o par (0, 0).

#### 10.4.6 Counting-Bases Page Replacement
**Least Frequently Used (LFU)**: substitui a página com menor contador (shifthing em intervalos de tempo).\
**Most Frequently Used (MFU)**

#### 10.4.7 Page Buffering Algorithms
Sempre que o paging device estiver parado, uma página modificada é selecionada e escrita no disco.\

### 10.5 Allocation of Frames
O user process recebe qualquer frame livre.

**Mininum Number of Frames**: Um número mínimo de frames alocados a cada processo é definido pela arquitetura.\
**Equal Allocation**: valor = total de frames / número de processos.
**Propotional Allocation**: valor é uma proporção de acordo com o número de páginas totais do processo.

### 10.6 Thrashing
Quando não há o mínimo de frames livres para um processo.\
Processo que gasta mais tempo em paging do que em execução.

## 11. Mass-Storage Structure
### 11.1 Overview
#### 11.1.1 Hard Disk Drives
**Positioning time** (ou **random access time**): tempo necessário para mover a cabeça do disco até a posição desejada.\
Está sujeito a danos físicos.

#### 11.1.2 Nonvolatile Memory Devices
Flash-memory-based NVM: SSDs\
Dados não podem ser sobrescritos, precisa-se apagar o bloco inteiro antes, normalmente, marca-se como dado inválido em vez de apagar, apagando apenas quando necessário.

#### 11.1.3 Volatile Memory
RAM Drives: memória RAM como disco rígido, criado por device drivers.

#### 11.1.4 Secondary storage connection methods
SATA, USB, ...\
O device controller está contido no dispositivo.

#### 11.1.5 Address Mapping
Blocos lógicos mapeiam para blocos físicos.

### 11.2 HDD Scheduling
**Bandwidth**: taxa de transferência de dados.\
Pode-se minimizar o numero de seeks ao se ordenar as requisições.

#### 11.2.1 FCFS Scheduling
FIFO

#### 11.2.2 SCAN Scheduling
O disco é percorrido em um sentido e depois no outro.\
Bom para heavy load.\
"Ideia de ir no caminho contrário ao chegar no fim."


#### 11.2.3 C-SCAN Scheduling
O disco é percorrido circularmente, chegando no fim, salta para o começo.\
Bom para heavy load.

### 11.3 NVM Scheduling
Política FCFS.

**Acesso sequencial**: bom para discos, pois dados estão próximos.\
**Acesso aleatório**: bom para NVM, pois não há cabeça.

## 12. I/O Systems
### 12.1 Overview
**Device drivers**: apresenta uma interface para o subsistema de I/O.

### 12.2 I/O Hardware
**Controller**: hardware que opera uma porta, dispositivo, etc.

#### 12.2.1 Memory Mapped I/O
O dispositivo é mapeado no espaço de endereço do processador.\
Consiste em quatro registradores:
* **Data-in register**: lido pelo host para receber o input.
* **Data-out register**: escrito pelo host para enviar o output.
* **Status register**: bits que indicam o status do dispositivo, pode ser lido pelo host.
* **Control register**: escrito pelo host para iniciar uma operaçã ou mudar o modo do dispositivo.

#### 12.2.2 Polling
O host verifica o status do dispositivo periodicamente, handshaking.
    
    1. Host le o busy bit repetidamente até que seja limpo (busy-waiting ou polling, loop)
    2. Host seta o write bit no command register, e escreve o dado no data-out register
    3. Host seta o command-ready bit
    4. Quando o controlador percebe que o command-ready bit está setado, seta o busy bit
    5. O controlador le o command register e ve o write command, então le o data-out e realiza o I/O no dispositivo
    6. O controlador limpa o command-ready bit, limpa o error bit no status register, limpa o busy bit (terminou o I/O)

#### 12.2.3 Interrupts
Mecanismo que permite ao dispositivo notificar a CPU.\
CPU sente o interrupt-request line após a execução de cada instrução.\
**Device controller dispara uma interrupção, a CPU captura a interrupção e a joga para o interrupt handler, que libera satisfazendo o dispositivo que disparou**.\
**nonmaskable interrupt**: interrupção que não pode ser desabilitada.\
**maskable interrupt**: interrupção que pode ser desabilitada pela CPU quando estiver executando instruções críticas.\
**interrupt vector**: tabela que contém os endereços dos interrupt handlers.\
**Interrupções possuem níveis de prioridade**.
**Trap**: interrupção que ocorre quando o processador executa uma instrução inválida ou tenta acessar uma região de memória não permitida.\

#### 12.2.4 Direct Memory Access (DMA)
**DMA controller**: controlador que opera o DMA.\
Mecanismo para evitar que a CPU fique ocupada com o I/O, então DMA controller faz o handshaking com o device controller e transfere os dados diretamente para a memória.\
*DMA request e DMA acknowledge*

Bloco de comando:
* **source**
* **target**
* **number of bytes**

### 12.3 Application I/O Interface
Sistema de IO independente do hardware.\
Existem diferentes tipos de I/O: sincrono, assincrono, acesso sequencial, randomico, velicade de operação, etc.

#### 12.3.1 Block and Character Devices
Teclado é um exemplo de character stream device.\

#### 12.3.2 Networking Devices
Network socket interface: ler e receber pacotes de dados.

#### 12.3.3 Clocks and Times
Tempo atual, tempo demorado, timers para disparar um evento num tempo futuro.

#### 12.3.4 Nonblocking and Asynchronous I/O
Blocking: a execução para até algo acontecer, a thread vai para fila de espera e depois volta para ready queue.\
Nonblocking: a execução não para, retorna algo ou nada.\
Asynchronous: a execução não para, mas o resultado é notificado posteriormente.

#### 12.3.5 Vectored I/O
Permite a uma syscall executar múltiplas operações de IO em múltiplos locais.

## 13. File-System Interface

### 13.1 File Concept
**Arquivo**: sequência de bytes com um nome, gravadas no armazenamento secundário.\
Text file, source file, executable file.

#### 13.1.1 File Attributes
Nomeado e referenciado pelo nome.
Possui:
* Nome
* Identificador
* Tipo
* Localização
* Tamanho
* Proteção (escrita, leitura, ...)
* Timestamps e identificação do usuário

#### 13.1.2 File Operations
* Create: espaço deve ser alocado e o arquivo deve ser inicializado.
* Open: todas as ops abrem o arquivo, exceto create e delete.
* Write
* Read
* Seek
* Truncate

**Open file table**: contém informações sobre todos os arquivos abertos.\
**Per process table**: rastreia todos os arquivos abertos por um processo.\
**System wide table**: contém a localização no disco dos arquivos abertos, datas de acesso, etc.

Informações associadas a um arquivo aberto:
* File pointer
* FIle-open count
* Location of the file
* Access rights

#### 13.1.3 File Types
Se o SO reconhece o tipo de arquivo, pode operar nele.

#### 13.1.4 File Structure
Alguns formatos devem satisfazer a uma determinada estrutura.\
O SO deve saber como interpretar o arquivo.

### 13.2 Access Methods
#### 13.2.1 Sequential Access
Processado em ordem, um registro após o outro (editores, compiladores).

#### 13.2.2 Direct Access
Acesso direto, sem ordem, por meio de blocos de tamanho fixo (DB).

#### 13.2.3 Indexed Access
Acesso direto, com índices

### 13.3 Directory Structure
Pode ser visto como um tabela de símbolos que traduz nomes aos file control blocks.\

Operações:
* Search for a file
* Create
* Delete
* List
* Rename
* Traverse the file system

#### 13.3.1 Single-Level Directory
Todos os arquivos estão no mesmo diretório.\
**Problema**: single user, nomes devem ser únicos.

#### 13.3.2 Two-Level Directory
Cada usuário tem seu diretório.\
**Path**: caminho para o arquivo.

#### 13.3.3 Tree-Structured Directory
Possui raiz e todo arquivo tem um único caminho.\
Um bit define o tipo
* 0: file
* 1: directory
Para deletar um diretório, deve-se apagar os arquivos e diretórios dentro dele (recursivo).

#### 13.3.4 Acyclic Graph Directory
Permite diretórios serem compartilhados entre diretórios.\
Mesmo arquivo em vários locais.\
**Link**: ponteiro para um arquivo ou diretório.\
**Problema**: um arquivo contém múltiplos caminhos absolutos, ao deletar, pode haver ponteiros para arquivos não existentes.

#### 13.3.5 General Graph Directory
Ciclos são permitidos.\
**Problema**: é necessário garbage collection

## 14. File-System Implementation
### 14.1 File-System Structure
* Um disco pode ser reescrito in place: ler, modificar e escrever no mesmo bloco
* Um disco pode acessar diretamente qualquer bloco de informação

Ordem baixo para cima:
* **Device**
* **I/O Control**: device drivers e interrupt handlers, "retrieve block 123"
* **Basic file system**: emite comandos genéricos aos device drivers apropriados, gerencia buffers e caches
* **File-organization module**: conhece os arquivos e seus logical blocks, gerencia espaços livres
* **Logical file system**: lida com os metadados dos arquivos, mantém a estrutura do arquivo por meio de File Control Blocks (FCB, ou inode), que contém informações do arquivo.
* **Application programs**

### 14.2 File-System Operations
#### 14.2.1 Overview
Possui:
* **Boot control block(por volume)**: infos para dar boot no SO
* **Volume control block(por volume)**: número de blocos, tamanho dos blocos, blocos livres (ponteiros e quantidade), etc.
* **Estrutura de diretório (por file system) é usado para organizar os arquivos**
* **Per-file FCB**: informações sobre o arquivo

As informações em memória(cache) são usadas para gerenciar o file system e aumentar a performance. Dados são carregados na montagem, atualizados pelas operações, e descartados no desmonte.

#### 14.2.2 Usage
Quando um processo fecha um arquivo, é removido do per-process table, e o contador no system-wide table do arquivo é decrementado. Se o contador chega a 0, o arquivo é fechado.

### 14.3 Directory Implementation
#### 14.3.1 Linear List
Lista linear dos nomes dos arquivos com ponteiros para os blocos de dados.\
**Problema**: time-consuming(busca para deletar, criar)

#### 14.3.2 Hash Table
Tabela hash dos nomes dos arquivos com ponteiros para os blocos de dados.\
**Problema**: Colisões e a função hash depende do tamanho da tabela.

### 14.4 Allocation Methods
#### 14.4.1 Contiguous Allocation
Cada arquivo ocupa o conjunto continuo de blocos.\
Para HDs, o numero de seeks é mínimo.\
**Suporta acesso direto e acesso sequencial.**
**Problema**: encontrar espaço para um novo arquivo, fragmentação externa (compactação afeta o desempenho), saber quanto de espaço alocar.

#### 14.4.2 Linked Allocation
Cada arquivo é uma linked list de blocos.\
**Problema**: Suporta apenas acesso sequencial, requer seek para cada ponteiro, fragmentação interna (ponteiros ocupam espaço, ou clusters).

#### 14.4.3 Indexed Allocation
Reune todos os ponteiros no index block.\
Suport acesso direito sem fragmentação externa.\
**Problema**: um bloco inteiro de index deve ser alocado, mesmo se usar apenas um ponteiro

### 14.5 Free-Space Management
#### 14.5.1 Bit vector (bitmap)
Um bit por bloco, 1 se livre, 0 se ocupado.\
**Problema**: ineficiente se todo o vetor não estiver em memória.

#### 14.5.2 Linked List
Lista ligada dos blocos livres.
#### 14.5.3 Grouping
Agrupar os blocos livres no primeiro bloco livre.

#### 14.5.4 Counting
Armazena o primeiro bloco livre e a quantidade de blocos livres (para blocos contínuos).

## 15. File-System Internal

### 15.1 File System

### 15.2 File System Mounting
File system deve ser montado antes de estar disponível

### 15.3 Partitions and Mouting
**Raw disk**: disco sem file system.\
Se a partição é bootavel, deve contem as informações de boot.\
**Bootstrap loader**: ecnontrar, carregar e executar o kernel.\
A **partição de boot** é montada em tempo de boot, contém o kernel e outros sistemas de arquivo.