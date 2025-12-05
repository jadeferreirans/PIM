<h1>Sistema Acadêmico – PIM II</h1>

<p>
    Este repositório contém o desenvolvimento de um Sistema modular criado como parte de um trabalho acadêmico, composto por um núcleo
    em linguagem C responsável por toda a lógica interna e uma interface Python utilizada para leitura
    e exibição dos dados persistidos.
</p>

<hr>

<h2>Descrição Geral</h2>

<h3>Núcleo em C</h3>
<ul>
    <li>Autenticação de usuários</li>
    <li>Gerenciamento de usuários (administrador, professor e aluno)</li>
    <li>CRUD de disciplinas</li>
    <li>Registro e edição de notas</li>
    <li>Registro e edição de faltas</li>
    <li>Consulta e edição de dados pessoais</li>
</ul>

<h3>Interface em Python</h3>
<p>
    A interface Python não se comunica diretamente com o executável em C.  
    Ela lê e interpreta os arquivos <code>.txt</code> gerados pelo módulo C, localizados em <code>/data</code>.
</p>

<hr>

<h2>Visao Geral do Projeto em C</h2>

<h3>Atores e Casos de Uso</h3>

<h3>Administrador</h3>
<ul>
    <li>Cadastrar usuários</li>
    <li>Editar usuários</li>
    <li>Excluir usuários</li>
    <li>Consultar usuários</li>
    <li>Gerenciar disciplinas (listar, criar, editar, excluir)</li>
    <li>Alterar sua própria senha</li>
</ul>

<h3>Professor</h3>
<ul>
    <li>Listar disciplinas ministradas</li>
    <li>Lançar notas</li>
    <li>Editar notas</li>
    <li>Lançar faltas</li>
    <li>Editar faltas</li>
    <li>Consultar e editar dados pessoais</li>
    <li>Alterar senha</li>
</ul>

<h3>Aluno</h3>
<ul>
    <li>Consultar notas</li>
    <li>Consultar faltas</li>
    <li>Consultar dados pessoais</li>
    <li>Editar dados pessoais</li>
    <li>Alterar senha</li>
</ul>

<h2>Estrutura do Projeto em C</h2>

<pre>
/proj_sistema_escolar/
│
├── main.c
├── usuario.c / usuario.h
├── professor.c / professor.h
├── aluno.c / aluno.h
├── disciplina.c / disciplina.h
├── notas.c / notas.h
├── menus.c / menus.h
│
└── /data/
     ├── usuarios.txt
     ├── professores.txt
     ├── alunos.txt
     ├── disciplinas.txt
     ├── notas.txt
     └── faltas.txt
</pre>

<div>
    <h3>Sobre os arquivos em /data</h3>
    <ul>
        <li>Todos os dados persistentes do sistema são armazenados nesse diretório.</li>
        <li>A interface Python lê exclusivamente esses arquivos.</li>
        <li>A estrutura e formatação são definidas pelo módulo C para garantir consistência.</li>
    </ul>
</div>

<hr>

<hr>

<h2>Interface Python</h2>

<p>
    A interface Python tem como objetivo principal interpretar os arquivos
    <code>.txt</code> gerados pelo módulo C e exibir informações de forma organizada.
</p>

<h3>A interface exibe:</h3>

<ul>
    <li>Notas</li>
    <li>Faltas</li>
    <li>Disciplinas</li>
    <li>Dados pessoais</li>
</ul>

<p>
    A interface atua apenas como camada de visualização e não interfere na lógica interna do sistema.
</p>

<hr>

<h2>Conteúdo do Repositório</h2>

<ul>
    <li>Código-fonte completo do sistema em C</li>
    <li>Interface Python para leitura dos arquivos</li>
    <li>Diagramas e artefatos de desenvolvimento</li>
</ul>
