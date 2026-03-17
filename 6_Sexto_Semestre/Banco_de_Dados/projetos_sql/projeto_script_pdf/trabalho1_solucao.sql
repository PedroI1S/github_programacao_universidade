-- Trabalho 1 — Fundamentos de Banco de Dados (UTFPR)
-- Solução em PostgreSQL
-- Observação: Exercícios resolvidos na ordem, com o enunciado copiado antes de cada resposta.

-- ============================================================================
-- Exercício 1 (30 pontos)
-- ENUNCIADO: "Faça a normalização até a terceira forma normal."
--
-- RESPOSTA: Ver documento NORMALIZACAO.md, que apresenta 1FN, 2FN e 3FN,
-- ============================================================================

-- ============================================================================
-- Exercício 2 (30 pontos)
-- ENUNCIADO: "Escreva o script SQL para criação dos dados: definindo os tipos de
-- dados adequados, as chaves primárias, únicas e estrangeiras. Definir restrições
-- de checagem e preenchimento obrigatório (quando for o caso)."
-- ============================================================================

DROP TABLE IF EXISTS imagem_local;
DROP TABLE IF EXISTS funcionalidade;
DROP TABLE IF EXISTS local;
DROP TABLE IF EXISTS responsaveis;
DROP TABLE IF EXISTS enderecos;

DROP TYPE IF EXISTS periodicidade_taxa;
CREATE TYPE periodicidade_taxa AS ENUM ('NULL','diaria','mensal','bimestral','trimestral');

CREATE TABLE IF NOT EXISTS enderecos (
  cep      VARCHAR(9) PRIMARY KEY NOT NULL,
  rua      VARCHAR(200) NOT NULL,
  bairro   VARCHAR(120) NOT NULL,
  cidade   VARCHAR(120) NOT NULL,
  uf       CHAR(2) NOT NULL,
  CONSTRAINT ck_enderecos_uf CHECK (uf ~ '^[A-Z]{2}$'),
  CONSTRAINT ck_enderecos_cep CHECK (cep ~ '^[0-9]{5}-?[0-9]{3}$')
);

CREATE TABLE IF NOT EXISTS responsaveis (
  responsavel_id INT PRIMARY KEY GENERATED ALWAYS AS IDENTITY,
  nome           VARCHAR(120) NOT NULL,
  celular        VARCHAR(20)  NOT NULL
);

CREATE TABLE IF NOT EXISTS local (
  id_cadastro         INT PRIMARY KEY GENERATED ALWAYS AS IDENTITY,
  nome_local          VARCHAR(200) NOT NULL,
  numero              VARCHAR(20)  NOT NULL,
  area                NUMERIC(12,2) NOT NULL,
  latitude            DECIMAL(9,6) NOT NULL,
  longitude           DECIMAL(9,6) NOT NULL,
  path_planta_baixa   TEXT,
  cep                 VARCHAR(9) NOT NULL,
  CONSTRAINT ck_local_area CHECK (area >= 0),
  CONSTRAINT ck_local_lat CHECK (latitude BETWEEN -90 AND 90),
  CONSTRAINT ck_local_lon CHECK (longitude BETWEEN -180 AND 180),
  CONSTRAINT fk_local_endereco FOREIGN KEY (cep) REFERENCES enderecos(cep) ON DELETE RESTRICT
);

CREATE TABLE IF NOT EXISTS imagem_local (
  id_exibicao     INT NOT NULL PRIMARY KEY,
  id_cadastro     INT NOT NULL,
  titulo_imagem   VARCHAR(200) NOT NULL,
  path            TEXT NOT NULL,
  CONSTRAINT ck_imagem_local_ordem CHECK (id_exibicao BETWEEN 1 AND 10),
  CONSTRAINT fk_imagem_local__local FOREIGN KEY (id_cadastro) REFERENCES local(id_cadastro) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS funcionalidade (
  id_funcionalidade    INT GENERATED ALWAYS AS IDENTITY,
  id_cadastro          INT NOT NULL,
  descricao_funcionalidade VARCHAR(200) NOT NULL,
  hora_abertura        TIME NOT NULL,
  hora_fechamento      TIME NOT NULL,
  lotacao_maxima       INT NOT NULL,
  taxa_uso             NUMERIC(10,2) NOT NULL,
  periodicidade_taxa   periodicidade_taxa,
  pets                 BOOLEAN NOT NULL,
  ativa                BOOLEAN NOT NULL,
  data_criacao         DATE NOT NULL,
  data_ultima_reforma  DATE,
  path_funcionalidade  TEXT,
  responsavel_id       INT NOT NULL,
  CONSTRAINT pk_funcionalidade PRIMARY KEY (id_funcionalidade, id_cadastro),
  CONSTRAINT ck_func_lotacao CHECK (lotacao_maxima > 0),
  CONSTRAINT ck_func_taxa CHECK (taxa_uso >= 0),
  CONSTRAINT ck_func_horario CHECK (hora_abertura < hora_fechamento),
  CONSTRAINT ck_func_taxa_periodicidade CHECK (
    (taxa_uso = 0 AND periodicidade_taxa = 'NULL') OR
    (taxa_uso > 0 AND periodicidade_taxa <> 'NULL')
  ),
  CONSTRAINT fk_func_local FOREIGN KEY (id_cadastro) REFERENCES local(id_cadastro) ON DELETE CASCADE,
  CONSTRAINT fk_func_responsavel FOREIGN KEY (responsavel_id) REFERENCES responsaveis(responsavel_id) ON DELETE RESTRICT
);

-- ============================================================================
-- Exercício 3 (10 pontos)
-- ENUNCIADO: "Faça um comando SQL para adicionar a coluna 'custo_ult_reforma'
-- na tabela de recursos do local."

ALTER TABLE IF EXISTS funcionalidade
  ADD COLUMN IF NOT EXISTS custo_ult_reforma NUMERIC(12,2)
  CHECK (custo_ult_reforma IS NULL OR custo_ult_reforma >= 0);

-- ============================================================================
-- Exercício 4 (10 pontos)
-- ENUNCIADO: "Escreva um comando SQL de inserção para cada relação."

INSERT INTO enderecos (cep, rua, bairro, cidade, uf) VALUES ('85501-000', 'Av. Brasil', 'Centro', 'Pato Branco', 'PR') ON CONFLICT (cep) DO NOTHING;
INSERT INTO enderecos (cep, rua, bairro, cidade, uf) VALUES ('85503-333', 'Rua Pequena', 'Centro', 'Pato Branco', 'PR') ON CONFLICT (cep) DO NOTHING;
INSERT INTO enderecos (cep, rua, bairro, cidade, uf) VALUES ('85504-444', 'Av. Gigante', 'Zona Sul', 'Pato Branco', 'PR') ON CONFLICT (cep) DO NOTHING;
INSERT INTO enderecos (cep, rua, bairro, cidade, uf) VALUES ('85505-555', 'Rua Média', 'Bairro Novo', 'Pato Branco', 'PR') ON CONFLICT (cep) DO NOTHING;
INSERT INTO enderecos (cep, rua, bairro, cidade, uf) VALUES ('85502-222', 'Rua dos Animais', 'Centro', 'Pato Branco', 'PR') ON CONFLICT (cep) DO NOTHING;
INSERT INTO local (nome_local, numero, area, latitude, longitude, path_planta_baixa, cep) VALUES ('Parque Pets', '50', 1200.00, -26.228500, -52.669900, '/docs/plantas/parque_pets.pdf', '85502-222');
INSERT INTO imagem_local (id_exibicao, id_cadastro, titulo_imagem, path) VALUES (1, currval(pg_get_serial_sequence('local','id_cadastro')), 'Entrada principal', '/imgs/locais/parque_central_entr.jpg');
INSERT INTO responsaveis (nome, celular) VALUES ('Maria Souza', '(46) 99999-0002');
INSERT INTO responsaveis (nome, celular) VALUES ('João Pets', '(46) 98888-0001');
INSERT INTO funcionalidade (id_cadastro, descricao_funcionalidade, hora_abertura, hora_fechamento, lotacao_maxima, taxa_uso, periodicidade_taxa, pets, ativa, data_criacao, data_ultima_reforma, path_funcionalidade, custo_ult_reforma, responsavel_id) VALUES (currval(pg_get_serial_sequence('local','id_cadastro')), 'Pista de Caminhada', '06:00', '21:00', 200, 0.00, 'NULL', TRUE, TRUE, '2019-08-01', NULL, '/imgs/func/pista.jpg', 4500.00, currval(pg_get_serial_sequence('responsaveis','responsavel_id')));
INSERT INTO funcionalidade (id_cadastro, descricao_funcionalidade, hora_abertura, hora_fechamento, lotacao_maxima,taxa_uso, periodicidade_taxa, pets, ativa, data_criacao, data_ultima_reforma, path_funcionalidade, custo_ult_reforma, responsavel_id) VALUES (currval(pg_get_serial_sequence('local','id_cadastro')), 'Pet Park', '08:00', '20:00', 80, 20.00, 'mensal', TRUE, TRUE, '2023-01-15', NULL, '/imgs/func/petpark.jpg', 1200.00, currval(pg_get_serial_sequence('responsaveis','responsavel_id')));


-- ============================================================================
-- Exercício 5 (10 pontos)
-- ENUNCIADO: "Com SQL, altere a taxa de uso de todas funcionalidades ativas que
-- aceitam pets, majorando em 10%."

UPDATE funcionalidade
   SET taxa_uso = ROUND(taxa_uso * 1.10, 2)
 WHERE ativa = TRUE AND pets = TRUE AND taxa_uso > 0;

-- ============================================================================
-- Exercício 6 (10 pontos)
-- ENUNCIADO: "Com SQL, exclua todos os locais esportivos que tenham área total
-- abaixo de 50 m² e acima de 50000 m²."

INSERT INTO local (
  nome_local, numero, area, latitude, longitude, path_planta_baixa, cep
) VALUES
('Micro Quadra', '1', 40.00, -26.227000, -52.668000, NULL, '85503-333'),
('Mega Arena',   '9999', 60001.00, -26.226000, -52.667000, NULL, '85504-444'),
('Quadra OK',    '100', 1000.00, -26.225000, -52.666000, NULL, '85505-555');

DELETE FROM local l
 WHERE l.area < 50 OR l.area > 50000;

-- ============================================================================
-- Durante a elaboração deste trabalho, todas as partes tiveram contribuições de ambas as partes. Quanto a normalização, o Rodrigo normalizou o documento até a 3FN, após isso houve uma discussão sobre a vericidade da 3FN.
-- Ademais, para a elaboração da implementação do banco de dados, o Pedro acabou por implementar boa parte do código, com excessão dos tipos de dados e restrainsts que foram discutidas de forma conjunta, e as restrições foram sugeridas pelo Rodrigo.