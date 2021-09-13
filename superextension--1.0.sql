CREATE OR REPLACE FUNCTION superfunction(IN integer, IN text,
    OUT f1 integer, OUT f2 text)
    RETURNS SETOF record
    AS 'MODULE_PATHNAME', 'superfunction'
    LANGUAGE C IMMUTABLE STRICT;