DROP TABLE IF EXISTS Vendas;
DROP TABLE IF EXISTS Clientes;
DROP TABLE IF EXISTS Disponiveis;
DROP TABLE IF EXISTS Veiculos;
DROP TABLE IF EXISTS Modelos;
DROP TABLE IF EXISTS Filiais;
DROP TABLE IF EXISTS Marcas;
DROP TABLE IF EXISTS Cidades;


CREATE TABLE Cidades (
    Cod_cidade INTEGER PRIMARY KEY AUTOINCREMENT,
    Nome_cidade VARCHAR(100) NOT NULL,
    UF CHAR(2) NOT NULL,
    Pais VARCHAR(50) NOT NULL
);

CREATE TABLE Marcas (
    Cod_Marca INTEGER PRIMARY KEY AUTOINCREMENT,
    Nome_Marca VARCHAR(100) NOT NULL,
    PaisOrigem VARCHAR(50)
);

CREATE TABLE Filiais (
    Cod_filial INTEGER PRIMARY KEY AUTOINCREMENT,
    Nome_filial VARCHAR(150) NOT NULL,
    Cidade_filial INTEGER,
    CONSTRAINT fk_filial_cidade
        FOREIGN KEY (Cidade_filial) REFERENCES Cidades(Cod_cidade)
);

CREATE TABLE Modelos (
    Cod_modelo INTEGER PRIMARY KEY AUTOINCREMENT,
    Nome_modelo VARCHAR(100) NOT NULL,
    Tipo_modelo VARCHAR(50),
    Cor_modelo VARCHAR(30),
    Cod_Marca INTEGER,
    CONSTRAINT fk_modelo_marca
        FOREIGN KEY (Cod_Marca) REFERENCES Marcas(Cod_Marca)
);

CREATE TABLE Veiculos (
    Cod_veiculo INTEGER PRIMARY KEY AUTOINCREMENT,
    Cod_Modelo INTEGER,
    Ano_Fab INTEGER NOT NULL,
    Ano_Modelo INTEGER NOT NULL,
    CONSTRAINT fk_veiculos_modelo
        FOREIGN KEY (Cod_Modelo) REFERENCES Modelos(Cod_modelo)
);

CREATE TABLE Disponiveis (
    Cod_modelo INTEGER,
    Cod_filial INTEGER,
    data DATE NOT NULL,
    Qtde INTEGER NOT NULL,
    valor_venda DECIMAL(10, 2) NOT NULL,
    CONSTRAINT pk_disponivel PRIMARY KEY (Cod_modelo, Cod_filial, data),
    CONSTRAINT fk_disponivel_modelo FOREIGN KEY (Cod_modelo) REFERENCES Modelos(Cod_modelo),
    CONSTRAINT fk_disponivel_filial FOREIGN KEY (Cod_filial) REFERENCES Filiais(Cod_filial)
);

--Exercico 1
CREATE TABLE Clientes (
    id_cliente INTEGER PRIMARY KEY AUTOINCREMENT,
    nome VARCHAR(150) NOT NULL,
    cpf VARCHAR(14) NOT NULL UNIQUE,
    endereco_completo TEXT,
    celular VARCHAR(20),
    email VARCHAR(100) UNIQUE,
    data_nascimento DATE
);

--Exercicio 2
CREATE TABLE Vendas (
    id_venda INTEGER PRIMARY KEY AUTOINCREMENT,
    data_venda DATE NOT NULL,
    id_cliente INTEGER NOT NULL,
    valor_total DECIMAL(10, 2) NOT NULL,
    cod_veiculo INTEGER NOT NULL UNIQUE,
    CONSTRAINT fk_venda_cliente
        FOREIGN KEY (id_cliente) REFERENCES Clientes(id_cliente),
    CONSTRAINT fk_venda_veiculo
        FOREIGN KEY (cod_veiculo) REFERENCES Veiculos(Cod_veiculo)
);

--Exercicio 3
ALTER TABLE Veiculos ADD COLUMN cor VARCHAR(30);
ALTER TABLE Veiculos ADD COLUMN placa VARCHAR(8) UNIQUE;
ALTER TABLE Veiculos ADD COLUMN chassi VARCHAR(17) NOT NULL UNIQUE;
ALTER TABLE Veiculos ADD COLUMN cod_filial INTEGER;

--Exercicio 4
INSERT INTO Marcas (Nome_Marca, PaisOrigem) VALUES ('Fiat', 'Itália'), ('Volkswagen', 'Alemanha'), ('Chevrolet', 'EUA'), ('Ford', 'EUA'), ('Toyota', 'Japão'), ('Honda', 'Japão'), ('Hyundai', 'Coreia do Sul'), ('Renault', 'França');
INSERT INTO Cidades (Nome_cidade, UF, Pais) VALUES ('Pato Branco', 'PR', 'Brasil'), ('Curitiba', 'PR', 'Brasil'), ('São Paulo', 'SP', 'Brasil'), ('Rio de Janeiro', 'RJ', 'Brasil'), ('Belo Horizonte', 'MG', 'Brasil'), ('Florianópolis', 'SC', 'Brasil'), ('Porto Alegre', 'RS', 'Brasil'), ('Salvador', 'BA', 'Brasil');
INSERT INTO Clientes (nome, cpf, endereco_completo, celular, email, data_nascimento) VALUES
('João da Silva', '111.111.111-11', 'Rua das Flores, 123, Pato Branco-PR', '(46) 99999-1111', 'joao.silva@email.com', '1990-05-15'), ('Maria Oliveira', '222.222.222-22', 'Avenida Brasil, 456, São Paulo-SP', '(11) 98888-2222', 'maria.o@email.com', '1985-09-20'),
('Pedro Souza', '333.333.333-33', 'Rua da Praia, 789, Rio de Janeiro-RJ', '(21) 97777-3333', 'pedro.souza@email.com', '1992-01-30'), ('Ana Costa', '444.444.444-44', 'Praça da Liberdade, 101, Belo Horizonte-MG', '(31) 96666-4444', 'ana.costa@email.com', '1998-11-12'),
('Lucas Pereira', '555.555.555-55', 'Avenida Beira Mar, 202, Florianópolis-SC', '(48) 95555-5555', 'lucas.p@email.com', '1988-07-07'), ('Juliana Ferreira', '666.666.666-66', 'Rua dos Andradas, 303, Porto Alegre-RS', '(51) 94444-6666', 'juliana.f@email.com', '1995-03-25'),
('Marcos Santos', '777.777.777-77', 'Avenida Oceânica, 404, Salvador-BA', '(71) 93333-7777', 'marcos.s@email.com', '1980-12-01'), ('Carla Lima', '888.888.888-88', 'Rua XV de Novembro, 505, Curitiba-PR', '(41) 92222-8888', 'carla.lima@email.com', '1993-08-18');
INSERT INTO Filiais (Nome_filial, Cidade_filial) VALUES ('Pato Branco Matriz', 1), ('Capital Curitiba', 2), ('Avenida Paulista', 3), ('Copacabana Motors', 4), ('Minas Car', 5), ('Ilha da Magia Veículos', 6), ('Porto Alegre Central', 7), ('Bahia Motors', 8);
INSERT INTO Modelos (Nome_modelo, Tipo_modelo, Cor_modelo, Cod_Marca) VALUES ('Argo', 'Hatch', 'Vermelho', 1), ('Polo', 'Hatch', 'Branco', 2), ('Onix', 'Hatch', 'Prata', 3), ('Ka', 'Hatch', 'Preto', 4), ('Corolla', 'Sedan', 'Cinza', 5), ('Civic', 'Sedan', 'Preto', 6), ('HB20', 'Hatch', 'Branco', 7), ('Kwid', 'Hatch', 'Laranja', 8);
INSERT INTO Veiculos (Cod_Modelo, Ano_Fab, Ano_Modelo, cor, placa, chassi, cod_filial) VALUES
(1, 2024, 2025, 'Vermelho Montecarlo', 'BCB1A23', '9BWZAA555P8T11111', 1), (2, 2024, 2024, 'Branco Cristal', 'DEF4B56', '9BWZAA555P8T22222', 2),
(3, 2025, 2025, 'Prata Switchblade', 'GHI7C89', '9BWZAA555P8T33333', 3), (5, 2024, 2025, 'Cinza Granito', 'JKL0D12', '9BWZAA555P8T44444', 5),
(6, 2025, 2025, 'Preto Cristal', 'MNO3E45', '9BWZAA555P8T55555', 4), (7, 2024, 2024, 'Branco Atlas', 'PQR6F78', '9BWZAA555P8T66666', 2),
(8, 2025, 2025, 'Laranja Ocre', 'STU9G01', '9BWZAA555P8T77777', 1), (1, 2024, 2025, 'Branco Banchisa', 'VWX2H34', '9BWZAA555P8T88888', 6);
INSERT INTO Disponiveis (Cod_modelo, Cod_filial, data, Qtde, valor_venda) VALUES (1, 1, '2025-09-12', 5, 85500.00), (2, 2, '2025-09-12', 10, 93000.00), (3, 3, '2025-09-12', 8, 92500.00), (4, 1, '2025-09-12', 3, 75000.00), (5, 5, '2025-09-12', 7, 152000.00), (6, 4, '2025-09-12', 4, 160000.00), (7, 2, '2025-09-12', 12, 88000.00), (8, 7, '2025-09-12', 6, 72000.00);
INSERT INTO Vendas (data_venda, id_cliente, valor_total, cod_veiculo) VALUES ('2025-05-10', 1, 85000.00, 1), ('2025-06-15', 2, 92000.00, 3), ('2025-07-20', 5, 150000.00, 4), ('2025-08-01', 8, 165000.00, 5);

--Exercicio 5
-- AJUSTE 1: Remover a tabela 'Disponiveis' que não é mais necessária
DROP TABLE Disponiveis;

-- AJUSTE 2: Adicionar um campo de status na tabela 'Veiculos' para clareza
ALTER TABLE Veiculos ADD COLUMN status VARCHAR(20) NOT NULL DEFAULT 'Disponível';

-- Atualiza o status dos veículos já vendidos para 'Vendido'
UPDATE Veiculos SET status = 'Vendido' WHERE Cod_veiculo IN (SELECT cod_veiculo FROM Vendas);


-- AJUSTE 3 e 4: Apresentar a estrutura ideal para as tabelas 'Modelos' e 'Clientes',
-- já que a remoção de colunas e a normalização exigem a recriação das tabelas.

-- Tabela Modelos (sem a coluna redundante 'Cor_modelo')
/*CREATE TABLE Modelos_Corrigida (
    Cod_modelo INTEGER PRIMARY KEY AUTOINCREMENT,
    Nome_modelo VARCHAR(100) NOT NULL,
    Tipo_modelo VARCHAR(50),
    Cod_Marca INTEGER,
    CONSTRAINT fk_modelo_marca FOREIGN KEY (Cod_Marca) REFERENCES Marcas(Cod_Marca)
);
-- Tabela Clientes (com o endereço normalizado e ligado à tabela Cidades)
CREATE TABLE Clientes_Corrigida (
    id_cliente INTEGER PRIMARY KEY AUTOINCREMENT,
    nome VARCHAR(150) NOT NULL,
    cpf VARCHAR(14) NOT NULL UNIQUE,
    logradouro VARCHAR(200),
    numero VARCHAR(10),
    bairro VARCHAR(100),
    cep VARCHAR(9),
    cod_cidade INTEGER,
    celular VARCHAR(20),
    email VARCHAR(100) UNIQUE,
    data_nascimento DATE,
    CONSTRAINT fk_cliente_cidade FOREIGN KEY (cod_cidade) REFERENCES Cidades(Cod_cidade)
);
*/

