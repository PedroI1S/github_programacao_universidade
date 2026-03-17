PRAGMA foreign_keys = ON;

-- remover tabelas na ordem das dependências
DROP TABLE IF EXISTS PrincipaisClientes;
DROP TABLE IF EXISTS Credenciada_FuncionariosSetor;
DROP TABLE IF EXISTS Credenciada_Marcas;
DROP TABLE IF EXISTS QuadroTecnico;
DROP TABLE IF EXISTS Credenciadas;
DROP TABLE IF EXISTS Cargos;
DROP TABLE IF EXISTS Enderecos;

-- tabela de endereços (CEP como chave)
CREATE TABLE Enderecos (
    CEP     CHAR(8) PRIMARY KEY CHECK (length(CEP) = 8 AND CEP GLOB '[0-9]*'),
    Endereco TEXT NOT NULL,
    Bairro   TEXT,
    Cidade   TEXT NOT NULL,
    UF       CHAR(2) NOT NULL CHECK (UF GLOB '[A-Z][A-Z]')
);

-- cargos técnicos
CREATE TABLE Cargos (
    ID_Cargo           INTEGER PRIMARY KEY AUTOINCREMENT,
    Nome_Cargo         TEXT NOT NULL,
    Capacitacao_Tecnica TEXT
);

-- credenciadas (referência a Enderecos via CEP) usando constraint nomeada
CREATE TABLE Credenciadas (
    ID_Credenciada    INTEGER PRIMARY KEY AUTOINCREMENT,
    Razao_Social      TEXT NOT NULL,
    Nome_Fantasia     TEXT,
    CNPJ              CHAR(14) UNIQUE NOT NULL CHECK (length(CNPJ) = 14 AND CNPJ GLOB '[0-9]*'),
    IE                TEXT,
    IM                TEXT,
    Email             TEXT,
    Homepage          TEXT,
    Contato           TEXT,
    CEP               CHAR(8) NOT NULL,
    Telefone          TEXT,
    Fax               TEXT,
    Regiao_Atendimento TEXT,
    CONSTRAINT fk_credenciadas_enderecos FOREIGN KEY (CEP) REFERENCES Enderecos(CEP)
);

-- quadro técnico: técnico ligado a uma credenciada e a um cargo (constraints nomeadas)
CREATE TABLE QuadroTecnico (
    ID_Tecnico      INTEGER NOT NULL,
    ID_Credenciada  INTEGER NOT NULL,
    Nome            TEXT NOT NULL,
    ID_Cargo        INTEGER NOT NULL,
    Data_Admissao   DATE DEFAULT (date('now')),
    PRIMARY KEY (ID_Tecnico, ID_Credenciada),
    CONSTRAINT fk_quadrotecnico_credenciada FOREIGN KEY (ID_Credenciada) REFERENCES Credenciadas(ID_Credenciada),
    CONSTRAINT fk_quadrotecnico_cargo FOREIGN KEY (ID_Cargo) REFERENCES Cargos(ID_Cargo)
);

-- marcas associadas à credenciada (constraint nomeada)
CREATE TABLE Credenciada_Marcas (
    ID_Marca        INTEGER PRIMARY KEY AUTOINCREMENT,
    ID_Credenciada  INTEGER NOT NULL,
    Nome_Marca      TEXT NOT NULL,
    CONSTRAINT fk_credenciada_marcas_credenciada FOREIGN KEY (ID_Credenciada) REFERENCES Credenciadas(ID_Credenciada)
);

-- quantidade de funcionários por setor na credenciada (constraint nomeada)
CREATE TABLE Credenciada_FuncionariosSetor (
    ID_FuncSetor    INTEGER PRIMARY KEY AUTOINCREMENT,
    ID_Credenciada  INTEGER NOT NULL,
    Setor           TEXT NOT NULL,
    Quantidade      INTEGER NOT NULL CHECK (Quantidade >= 0),
    CONSTRAINT fk_funcsetor_credenciada FOREIGN KEY (ID_Credenciada) REFERENCES Credenciadas(ID_Credenciada)
);

-- principais clientes atendidos pela credenciada (constraint nomeada)
CREATE TABLE PrincipaisClientes (
    ID_Cliente      INTEGER,
    ID_Credenciada  INTEGER NOT NULL,
    Nome_Cliente    TEXT NOT NULL,
    Telefone_Cliente TEXT,
    Contato_Cliente TEXT,
    PRIMARY KEY (ID_Cliente, ID_Credenciada),
    CONSTRAINT fk_principaisclientes_credenciada FOREIGN KEY (ID_Credenciada) REFERENCES Credenciadas(ID_Credenciada)
);
