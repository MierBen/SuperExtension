
#include <postgres.h>
#include <funcapi.h>

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(superfunction);

/**
 * @brief Создает строку из повторяющихся aaa символов
 * 
 * @param counter - кол-во элементов для повторения
 * @param str - строка с результатом
 */
void create_aaa_string(size_t counter, char *str);

/**
 * @brief Возвращает количество символов в числе
 * 
 * @param number - Целевое число
 * @return size_t - количество цифр
 */
size_t count_digits(size_t number); 

/**
 * @brief Функция, возвращающая повторяющееся значение A от 1..N
 * 
 * @return Datum 
 */
Datum
    superfunction(PG_FUNCTION_ARGS)
{

    // Инициализируем переменные
    FuncCallContext *funcctx = NULL;
    int call_cntr = 0;
    int max_calls = 0;
    TupleDesc tupdesc = { 0 };
    AttInMetadata *attinmeta = NULL;

    // Выполнение контекста при первом вызове функции
    if (SRF_IS_FIRSTCALL())
    {
        MemoryContext oldcontext = { 0 };

        // Инициализация контекста
        funcctx = SRF_FIRSTCALL_INIT();

        // Переключение на контекст мультивызова функции
        oldcontext = MemoryContextSwitchTo(funcctx->multi_call_memory_ctx);

        // Максимальное значение вызовов равно значению первого аргумента - counter
        funcctx->max_calls = PG_GETARG_UINT32(0);

        // 
        if (get_call_result_type(fcinfo, NULL, &tupdesc) != TYPEFUNC_COMPOSITE)
            ereport(ERROR,
                    (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
                     errmsg("function returning record called in context "
                            "that cannot accept type record")));

        // Сохранение метаданных для дальнешего создания кортежа
        attinmeta = TupleDescGetAttInMetadata(tupdesc);
        funcctx->attinmeta = attinmeta;

        MemoryContextSwitchTo(oldcontext);
    }

    // Инициализация контекста при каждом вызове функции
    funcctx = SRF_PERCALL_SETUP();

    call_cntr = funcctx->call_cntr;
    max_calls = funcctx->max_calls;
    attinmeta = funcctx->attinmeta;

    if (call_cntr < max_calls) // Выполняем до N
    {
        char **values = NULL;
        HeapTuple tuple;
        Datum result;
        const size_t counter = call_cntr + 1;
	const size_t digits = count_digits(counter);

        // Подготовка строк для хранения возвращающегося значения
        values = (char **)palloc(2 * sizeof(char *));

        values[0] = (char *)palloc((digits + 1) * sizeof(char));

        // Выделяем значение под значение + null-byte
        values[1] = (char *)palloc((counter + 1) * sizeof(char)); 

        snprintf(values[0], digits + 1, "%u", counter);

        // Обнуляем содержимое
        memset(values[1], 0, sizeof((counter + 1) * sizeof(char)) );
	// 
        create_aaa_string(counter, values[1]);

        // Создаем кортеж
        tuple = BuildTupleFromCStrings(attinmeta, values);

	elog(LOG, " %s | %s ", values[0], values[1]);

        // Преобразование tuple в Datum
        result = HeapTupleGetDatum(tuple);

        pfree(values[0]);
        pfree(values[1]);
        pfree(values);

        SRF_RETURN_NEXT(funcctx, result);
    }
    else
    {
        SRF_RETURN_DONE(funcctx);
    }
}

void create_aaa_string(size_t counter, char *str)
{
    if (counter == 0 || str == NULL)
    {
        return;
    }

    for (size_t i = 0; i < counter; i++)
    {
        strcat(str, "A");
    }
}

size_t count_digits(size_t number)
{
    size_t result = 0;

    while(number)
    {
	result++;
        number = number / 10;
    }

    return result;
}
