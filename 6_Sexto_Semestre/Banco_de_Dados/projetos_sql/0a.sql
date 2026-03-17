DROP TABLE IF EXISTS Veiculo;
DROP TABLE IF EXISTS Modelo;
DROP TABLE IF EXISTS Marca;
DROP TABLE IF EXISTS Motorista;
DROP TABLE IF EXISTS Departamento;
DROP TABLE IF EXISTS Funcionarios;

CREATE TABLE Funcionarios (
    CPF VARCHAR(11) PRIMARY KEY,
    Primeiro_Nome VARCHAR(50),
    Nome_do_Meio VARCHAR(50),
    Sobrenome VARCHAR(50),
    Data_de_Nascimento DATE,
    Genero CHAR(1)
);

CREATE TABLE Departamento (
    Codigo INT PRIMARY KEY,
    Nome VARCHAR(100),
    Numero_de_funcionarios INT,
    CPF_Gerente VARCHAR(11),
    CONSTRAINT fk_departamento_gerente FOREIGN KEY (CPF_Gerente) REFERENCES Funcionarios(CPF)
);

CREATE TABLE Motorista (
    CPF VARCHAR(11) PRIMARY KEY,
    CNH VARCHAR(20),
    Salario DECIMAL(10, 2),
    CPF_Supervisor VARCHAR(11),
    Departamento_Codigo INT,
    CONSTRAINT fk_motorista_funcionario FOREIGN KEY (CPF) REFERENCES Funcionarios(CPF),
    CONSTRAINT fk_motorista_supervisor FOREIGN KEY (CPF_Supervisor) REFERENCES Funcionarios(CPF),
    CONSTRAINT fk_motorista_departamento FOREIGN KEY (Departamento_Codigo) REFERENCES Departamento(Codigo)
);

CREATE TABLE Marca (
    Codigo INT PRIMARY KEY,
    Nome VARCHAR(100)
);

CREATE TABLE Modelo (
    Codigo INT PRIMARY KEY,
    Nome VARCHAR(100),
    Marca_Codigo INT,
    CONSTRAINT fk_modelo_marca FOREIGN KEY (Marca_Codigo) REFERENCES Marca(Codigo)
);

CREATE TABLE Veiculo (
    Placa VARCHAR(7) PRIMARY KEY,
    Renavam VARCHAR(11),
    Ano_modelo INT,
    Ano_de_fabricacao INT,
    Modelo_Codigo INT,
    Kilometragem DECIMAL(10, 2),
    Chassi VARCHAR(17),
    CONSTRAINT fk_veiculo_modelo FOREIGN KEY (Modelo_Codigo) REFERENCES Modelo(Codigo)
);


ALTER TABLE Motorista ADD COLUMN Email VARCHAR(255);
ALTER TABLE Motorista ADD COLUMN Celular VARCHAR(20);
ALTER TABLE Funcionarios DROP COLUMN Nome_do_Meio;
