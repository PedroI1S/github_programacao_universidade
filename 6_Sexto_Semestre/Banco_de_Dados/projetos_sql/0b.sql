DROP TABLE IF EXISTS Disponivel;
DROP TABLE IF EXISTS Veiculos;
DROP TABLE IF EXISTS Filial;
DROP TABLE IF EXISTS Modelo;
DROP TABLE IF EXISTS Cidade;
DROP TABLE IF EXISTS Marca;

-- Exercico 2
CREATE TABLE Marca (
    Cod_Marca INTEGER PRIMARY KEY AUTOINCREMENT,
    Nome_Marca VARCHAR(100) NOT NULL,
    PaisOrigem VARCHAR(50)
);

CREATE TABLE Cidade (
    Cod_cidade INTEGER PRIMARY KEY AUTOINCREMENT,
    Nome_cidade VARCHAR(100) NOT NULL,
    UF CHAR(2) NOT NULL,
    Pais VARCHAR(50) NOT NULL
);

CREATE TABLE Modelo (
    Cod_modelo INTEGER PRIMARY KEY AUTOINCREMENT,
    Nome_modelo VARCHAR(100) NOT NULL,
    Tipo_modelo VARCHAR(50),
    Cor_modelo VARCHAR(30),
    Cod_Marca INTEGER,
    CONSTRAINT fk_modelo_marca
        FOREIGN KEY (Cod_Marca)
        REFERENCES Marca(Cod_Marca)
);

CREATE TABLE Filial (
    Cod_filial INTEGER PRIMARY KEY AUTOINCREMENT,
    Nome_filial VARCHAR(150) NOT NULL,
    Cidade_filial INTEGER,
    CONSTRAINT fk_filial_cidade
        FOREIGN KEY (Cidade_filial)
        REFERENCES Cidade(Cod_cidade)
);

CREATE TABLE Veiculos (
    Cod_veiculo INTEGER PRIMARY KEY AUTOINCREMENT,
    Cod_Modelo INTEGER,
    Ano_Fab INTEGER NOT NULL,
    Ano_Modelo INTEGER NOT NULL,
    CONSTRAINT fk_veiculos_modelo
        FOREIGN KEY (Cod_Modelo)
        REFERENCES Modelo(Cod_modelo)
);

CREATE TABLE Disponivel (
    Cod_modelo INTEGER,
    Cod_filial INTEGER,
    data DATE NOT NULL,
    Qtde INTEGER NOT NULL,
    valor_venda DECIMAL(10, 2) NOT NULL,
    CONSTRAINT pk_disponivel
        PRIMARY KEY (Cod_modelo, Cod_filial, data),
    CONSTRAINT fk_disponivel_modelo
        FOREIGN KEY (Cod_modelo)
        REFERENCES Modelo(Cod_modelo),
    CONSTRAINT fk_disponivel_filial
        FOREIGN KEY (Cod_filial)
        REFERENCES Filial(Cod_filial)
);

-- Exercico 3
ALTER TABLE Modelo
ADD COLUMN Chassi VARCHAR(17) UNIQUE;

-- Exercico 4
ALTER TABLE Filial
ADD COLUMN Email VARCHAR(100);

ALTER TABLE Filial
ADD COLUMN Telefone VARCHAR(20);

-- Exercico 5
CREATE UNIQUE INDEX idx_cidade_filial_unica ON Filial (Cidade_filial);

-- Exercico 8
ALTER TABLE Veiculos
ADD CONSTRAINT chk_ano_fab_modelo CHECK (Ano_Fab <= Ano_Modelo);

ALTER TABLE Disponivel
ADD CONSTRAINT chk_qtde_positiva CHECK (Qtde >= 0);

ALTER TABLE Disponivel
ADD CONSTRAINT chk_valor_venda_positivo CHECK (valor_venda > 0);

ALTER TABLE Cidade
ADD CONSTRAINT chk_uf_formato CHECK (LENGTH(UF) = 2);