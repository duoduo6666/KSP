#include "esp_err.h"
#include "krpc.pb-c.h"

// malloc 可能会因为内存不足引发异常 这里没有异常处理
#define KRPC_CREATE_REQUEST(name, numbr) Krpc__Schema__Request name = KRPC__SCHEMA__REQUEST__INIT; \
    name.n_calls = numbr; \
    name.calls = malloc(sizeof(Krpc__Schema__ProcedureCall*) * name.n_calls);
#define KRPC_REQUEST_CAll(name) Krpc__Schema__ProcedureCall name = KRPC__SCHEMA__PROCEDURE_CALL__INIT;
#define KRPC_CALL_SpaceCenter_UT(name, request, pos) \
    KRPC_REQUEST_CAll(name); \
    name.service = "SpaceCenter"; name.procedure = "get_UT"; \
    request.calls[pos] = &name;
#define KRPC_CALL_SpaceCenter_ActiveVessel(name, request, pos) \
    KRPC_REQUEST_CAll(name); \
    name.service = "SpaceCenter"; name.procedure = "get_ActiveVessel"; \
    request.calls[pos] = &name;
#define KRPC_CALL_Vessel_Flight(name, request, pos, Vessel) \
    KRPC_REQUEST_CAll(name); \
    name.service = "SpaceCenter"; name.procedure = "Vessel_Flight"; \
    name.n_arguments = 1; name.arguments = malloc(sizeof(Krpc__Schema__Argument*) * name.n_arguments);\
    name.arguments[0] = &Vessel; \
    request.calls[pos] = &name;


esp_err_t encode_varint(uint32_t value, uint8_t **varint_buf, size_t *varint_len);
uint32_t decode_varint(uint8_t *varint_buf, size_t varint_len);
esp_err_t encode_double(double value, uint8_t **double_buf, size_t *double_len);
double decode_double(uint8_t *double_buf, size_t double_len);

esp_err_t krpc_connect();
esp_err_t krpc_GetStatus();
esp_err_t krpc_Request(Krpc__Schema__Request *request, Krpc__Schema__Response **response);

