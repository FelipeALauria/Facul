-- Questão 5
-- a
SELECT DISTINCT x.nome_empregado
FROM trabalha AS x
WHERE x.nome_companhia = 'XYZ Ltda'
ORDER BY x.nome_empregado
-- 

-- b
SELECT DISTINCT x.cidade
FROM empregado AS x, trabalha AS y
WHERE x.nome_empregado = y.nome_empregado
    AND y.nome_companhia = 'XYZ Ltda'
ORDER BY x.cidade
--

-- c 
SELECT DISTINCT x.nome_empregado, x.cidade, x.rua
FROM empregado AS X, trabalha AS y
WHERE x.nome_empregado = y.nome_empregado
    AND y.nome_companhia = 'XYZ Ltda'
    AND y.salario > 10000
ORDER BY x.nome_empregado, x.cidade, x.rua
-- Nessa query utilizei as tabelas empregado e trabalha para conseguir localizar os empregados que trabalham na companhia XYZ Ltda e que ganham mais de 10000 dolares. Também utilizei a cláusula DISTINCT para evitar duplicatas de empregados e ordenei o resultado pelo nome do empregado, cidade e rua.

-- c alternativa
SELECT DISTINCT x.nome empregado, x.rua, x.cidade
FROM empregado AS x
WHERE x.nome_empregado = ANY (
    SELECT DISTINCT y.nome_empregado
    FROM trabalha AS y
    WHERE y.nome_companhia = 'XYZ Ltda'
        AND y.salario > 10000
) 
-- 

-- d
SELECT DISTINCT x.nome_empregado, x.cidade
FROM empregado AS x, trabalha AS y, companhia AS z
WHERE x.nome_empregado = y.nome_empregado
    AND y.nome_companhia = z.nome_companhia
    AND x.cidade = z.cidade
ORDER BY x.nome_empregado, x.cidade
-- Nessa query utilizei a cláusula DISTINCT para evitar duplicatas de empregados. Fiz também o uso de joins entre as tabelas empregado, trabalha e companhia para garantir que os empregados estão associados às companhias e suas respectivas cidades.

-- d alternativa
SELECT DISTINCT x.nome_empregado, x.cidade
FROM empregado AS x
WHERE x.cidade = ANY (
    SELECT DISTINCT y.cidade
    FROM trabalha AS y, companhia AS z
    WHERE y.nome_companhia = z.nome_companhia
        AND z.cidade = x.cidade
) 
-- Nessa query utilizei a clásula DISTINCT para evitar duplicatas de empregados. Fiz também o uso da cláusula ANY para verificar se a cidade do empregado está presente na subconsulta que retorna as cidades das companhias, caso as cidades sejam identicas o funcionário cumpre a clásula do WHERE e é selcionado.

-- e
SELECT DISTINCT x.nome_empregado
FROM empregado AS x
WHERE (x.rua, x.cidade) IN (
    SELECT y.rua, y.cidade
    FROM gerente AS z, empregado AS y
    WHERE z.nome_gerente = y.nome_empregado
)


-- f
SELECT x.nmoe_empregado
FROM empregado AS x
WHERE x.nome_empregado NOT IN (
    SELECT y.nome_empregado
    FROM trabalha AS y
    WHERE y.nome_companhia = 'XYZ Ltda'
)


-- g
SELECT y.nome_empregado
FROM trabalha AS y
WHERE y.salario > ALL (
    SELECT z.salario
    FROM trabalha AS z
    WHERE z.nome_companhia = 'Byte Corporation'
)


-- 6)
-- a


σ(sexo = 'm')(cliente) = SELECT * FROM cliente WHERE sexo = 'm'


π(nome)(σsexo = 'm'(cliente)) = SELECT nome_cliente FROM cliente WHERE sexo = 'm'



SELECT x.nome_pessoa
FROM trabalha AS y, gerencia AS x
WHERE y.nome_pessoa = x.nome_pessoa
AND x.nome_gerente = 'Nestor da Silva' 
AND y.salario IN (
    SELECT z.salario
    FROM trabalha AS z, trabalha AS w
    WHERE z.salario > AVG(w.salario)
    AND z.nome_companhia = w.nome_companhia
    AND z.tipo_servico = w.tipo_servico
    )



SELECT x.nome_pessoa, x.salario
FROM pessoa AS x
WHERE x.salario IN (
    SELECT c.salario
    FROM pessoas AS a, gerencia AS b, pessoas AS c
    WHERE a.nome_pessoa = b.nome_pessoa
    AND b.nome_gerente = 'João Antonio'
    AND c.salario > a.salario
)


    --2)
    --a)
    SELECT x.nome_empregado, x.salario
    FROM pessoas AS x
    WHERE x.salario > ALL (
        SELECT y.salario
        FROM pessoa AS y, gerencia AS z
        WHERE z.nome_gerente = 'João Antonio'
        AND y.nome_empregado = z.nome_empregado
    )

    -- b)
    SELECT x.nome_empregado
    FROM pessoas AS x
    WHERE x.salario IN (
        SELECT y.salaio
        FROM trabalha AS y, trabalha AS z
        WHERE y.salario > AVG(z.salario)
        AND y.tipo_servico = z.tipo_servico
    )       

    -- c)
    SELECT y.nome_gerente
    FROM gerencia AS y, pessoas AS x
    WHERE y.nome_empregado = x.nome_empregado
    AND x.cidade IN (
        SELECT z.cidade
        FROM gerente AS w, pessoas AS z
        WHERE w.nome_gerente = 'Nestor da Silva'
        AND w.nome_empregado = z.nome_empregado
    )
