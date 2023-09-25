#include "crc32.h"
#include "crc32_base.h"
#include "crc32_bzip2.h"
#include "crc32_c.h"
#include "crc32_d.h"
#include "crc32_jamcrc.h"
#include "crc32_mpeg2.h"
#include "crc32_posix.h"
#include "crc32_q.h"
#include "crc32_xfer.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Crc32);

static uint8_t message1[] = { 0x00U, 0x00U, 0x00U, 0x00U };
static uint8_t message2[] = { 0xF2U, 0x01U, 0x83U };
static uint8_t message3[] = { 0x0FU, 0xAAU, 0x00U, 0x55U };
static uint8_t message4[] = { 0x00U, 0xFFU, 0x55U, 0x11U };
static uint8_t message5[] = { 0x33U, 0x22U, 0x55U, 0xAAU, 0xBBU, 0xCCU, 0xDDU, 0xEEU, 0xFFU };
static uint8_t message6[] = { 0x92U, 0x6BU, 0x55U };
static uint8_t message7[] = { 0xFFU, 0xFFU, 0xFFU, 0xFFU };

static uint32_t init_value = 0xFFFFFFFFU;
static uint32_t crc_xor_value = 0xFFFFFFFFU;

/* Table for CRC32 also know as Ethernet CRC (Polynomial 0x4C11DB7) */
static const uint32_t crc32_table[256] = {
    0x00000000U, 0x04C11DB7U, 0x09823B6EU, 0x0D4326D9U, 0x130476DCU, 0x17C56B6BU, 0x1A864DB2U, 0x1E475005U,
    0x2608EDB8U, 0x22C9F00FU, 0x2F8AD6D6U, 0x2B4BCB61U, 0x350C9B64U, 0x31CD86D3U, 0x3C8EA00AU, 0x384FBDBDU,
    0x4C11DB70U, 0x48D0C6C7U, 0x4593E01EU, 0x4152FDA9U, 0x5F15ADACU, 0x5BD4B01BU, 0x569796C2U, 0x52568B75U,
    0x6A1936C8U, 0x6ED82B7FU, 0x639B0DA6U, 0x675A1011U, 0x791D4014U, 0x7DDC5DA3U, 0x709F7B7AU, 0x745E66CDU,
    0x9823B6E0U, 0x9CE2AB57U, 0x91A18D8EU, 0x95609039U, 0x8B27C03CU, 0x8FE6DD8BU, 0x82A5FB52U, 0x8664E6E5U,
    0xBE2B5B58U, 0xBAEA46EFU, 0xB7A96036U, 0xB3687D81U, 0xAD2F2D84U, 0xA9EE3033U, 0xA4AD16EAU, 0xA06C0B5DU,
    0xD4326D90U, 0xD0F37027U, 0xDDB056FEU, 0xD9714B49U, 0xC7361B4CU, 0xC3F706FBU, 0xCEB42022U, 0xCA753D95U,
    0xF23A8028U, 0xF6FB9D9FU, 0xFBB8BB46U, 0xFF79A6F1U, 0xE13EF6F4U, 0xE5FFEB43U, 0xE8BCCD9AU, 0xEC7DD02DU,
    0x34867077U, 0x30476DC0U, 0x3D044B19U, 0x39C556AEU, 0x278206ABU, 0x23431B1CU, 0x2E003DC5U, 0x2AC12072U,
    0x128E9DCFU, 0x164F8078U, 0x1B0CA6A1U, 0x1FCDBB16U, 0x018AEB13U, 0x054BF6A4U, 0x0808D07DU, 0x0CC9CDCAU,
    0x7897AB07U, 0x7C56B6B0U, 0x71159069U, 0x75D48DDEU, 0x6B93DDDBU, 0x6F52C06CU, 0x6211E6B5U, 0x66D0FB02U,
    0x5E9F46BFU, 0x5A5E5B08U, 0x571D7DD1U, 0x53DC6066U, 0x4D9B3063U, 0x495A2DD4U, 0x44190B0DU, 0x40D816BAU,
    0xACA5C697U, 0xA864DB20U, 0xA527FDF9U, 0xA1E6E04EU, 0xBFA1B04BU, 0xBB60ADFCU, 0xB6238B25U, 0xB2E29692U,
    0x8AAD2B2FU, 0x8E6C3698U, 0x832F1041U, 0x87EE0DF6U, 0x99A95DF3U, 0x9D684044U, 0x902B669DU, 0x94EA7B2AU,
    0xE0B41DE7U, 0xE4750050U, 0xE9362689U, 0xEDF73B3EU, 0xF3B06B3BU, 0xF771768CU, 0xFA325055U, 0xFEF34DE2U,
    0xC6BCF05FU, 0xC27DEDE8U, 0xCF3ECB31U, 0xCBFFD686U, 0xD5B88683U, 0xD1799B34U, 0xDC3ABDEDU, 0xD8FBA05AU,
    0x690CE0EEU, 0x6DCDFD59U, 0x608EDB80U, 0x644FC637U, 0x7A089632U, 0x7EC98B85U, 0x738AAD5CU, 0x774BB0EBU,
    0x4F040D56U, 0x4BC510E1U, 0x46863638U, 0x42472B8FU, 0x5C007B8AU, 0x58C1663DU, 0x558240E4U, 0x51435D53U,
    0x251D3B9EU, 0x21DC2629U, 0x2C9F00F0U, 0x285E1D47U, 0x36194D42U, 0x32D850F5U, 0x3F9B762CU, 0x3B5A6B9BU,
    0x0315D626U, 0x07D4CB91U, 0x0A97ED48U, 0x0E56F0FFU, 0x1011A0FAU, 0x14D0BD4DU, 0x19939B94U, 0x1D528623U,
    0xF12F560EU, 0xF5EE4BB9U, 0xF8AD6D60U, 0xFC6C70D7U, 0xE22B20D2U, 0xE6EA3D65U, 0xEBA91BBCU, 0xEF68060BU,
    0xD727BBB6U, 0xD3E6A601U, 0xDEA580D8U, 0xDA649D6FU, 0xC423CD6AU, 0xC0E2D0DDU, 0xCDA1F604U, 0xC960EBB3U,
    0xBD3E8D7EU, 0xB9FF90C9U, 0xB4BCB610U, 0xB07DABA7U, 0xAE3AFBA2U, 0xAAFBE615U, 0xA7B8C0CCU, 0xA379DD7BU,
    0x9B3660C6U, 0x9FF77D71U, 0x92B45BA8U, 0x9675461FU, 0x8832161AU, 0x8CF30BADU, 0x81B02D74U, 0x857130C3U,
    0x5D8A9099U, 0x594B8D2EU, 0x5408ABF7U, 0x50C9B640U, 0x4E8EE645U, 0x4A4FFBF2U, 0x470CDD2BU, 0x43CDC09CU,
    0x7B827D21U, 0x7F436096U, 0x7200464FU, 0x76C15BF8U, 0x68860BFDU, 0x6C47164AU, 0x61043093U, 0x65C52D24U,
    0x119B4BE9U, 0x155A565EU, 0x18197087U, 0x1CD86D30U, 0x029F3D35U, 0x065E2082U, 0x0B1D065BU, 0x0FDC1BECU,
    0x3793A651U, 0x3352BBE6U, 0x3E119D3FU, 0x3AD08088U, 0x2497D08DU, 0x2056CD3AU, 0x2D15EBE3U, 0x29D4F654U,
    0xC5A92679U, 0xC1683BCEU, 0xCC2B1D17U, 0xC8EA00A0U, 0xD6AD50A5U, 0xD26C4D12U, 0xDF2F6BCBU, 0xDBEE767CU,
    0xE3A1CBC1U, 0xE760D676U, 0xEA23F0AFU, 0xEEE2ED18U, 0xF0A5BD1DU, 0xF464A0AAU, 0xF9278673U, 0xFDE69BC4U,
    0x89B8FD09U, 0x8D79E0BEU, 0x803AC667U, 0x84FBDBD0U, 0x9ABC8BD5U, 0x9E7D9662U, 0x933EB0BBU, 0x97FFAD0CU,
    0xAFB010B1U, 0xAB710D06U, 0xA6322BDFU, 0xA2F33668U, 0xBCB4666DU, 0xB8757BDAU, 0xB5365D03U, 0xB1F740B4U
};

TEST_SETUP(Crc32) {
}

TEST_TEAR_DOWN(Crc32) {
}

TEST_GROUP_RUNNER(Crc32) {
    RUN_TEST_CASE(Crc32, Crc32Base_tableCalculator);
    RUN_TEST_CASE(Crc32, CRC32Base_Reflect_output_and_input);
    RUN_TEST_CASE(Crc32, CRC32Base_Reflect_input);
    RUN_TEST_CASE(Crc32, CRC32Base_Reflect_output);
    RUN_TEST_CASE(Crc32, CRC32Base_Without_finish_xor);

    RUN_TEST_CASE(Crc32, Crc32);
    RUN_TEST_CASE(Crc32, Crc32_bzip2);
    RUN_TEST_CASE(Crc32, Crc32_c);
    RUN_TEST_CASE(Crc32, Crc32_d);
    RUN_TEST_CASE(Crc32, Crc32_jamcrc);
    RUN_TEST_CASE(Crc32, Crc32_mpeg2);
    RUN_TEST_CASE(Crc32, Crc32_posix);
    RUN_TEST_CASE(Crc32, Crc32_q);
    RUN_TEST_CASE(Crc32, Crc32_xfer);
}

TEST(Crc32, Crc32Base_tableCalculator) {

    uint32_t polynomial = 0x4C11DB7;
    uint32_t crc_table_calc[256];
    Crc32Base_tableCalculator(polynomial, crc_table_calc);
    TEST_ASSERT_EQUAL_HEX32_ARRAY(crc32_table, crc_table_calc, 256);
}


TEST(Crc32, CRC32Base_Reflect_output_and_input) {
    TEST_ASSERT_EQUAL_HEX32(0x2144DF1CU, Crc32Base(crc32_table, message1, sizeof(message1), init_value, crc_xor_value,
                            true, true, true));
    TEST_ASSERT_EQUAL_HEX32(0x24AB9D77U, Crc32Base(crc32_table, message2, sizeof(message2), init_value, crc_xor_value,
                            true, true, true));
    TEST_ASSERT_EQUAL_HEX32(0xB6C9B287U, Crc32Base(crc32_table, message3, sizeof(message3), init_value, crc_xor_value,
                            true, true, true));
    TEST_ASSERT_EQUAL_HEX32(0x32A06212U, Crc32Base(crc32_table, message4, sizeof(message4), init_value, crc_xor_value,
                            true, true, true));
    TEST_ASSERT_EQUAL_HEX32(0xB0AE863DU, Crc32Base(crc32_table, message5, sizeof(message5), init_value, crc_xor_value,
                            true, true, true));
    TEST_ASSERT_EQUAL_HEX32(0x9CDEA29BU, Crc32Base(crc32_table, message6, sizeof(message6), init_value, crc_xor_value,
                            true, true, true));
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFFFFU, Crc32Base(crc32_table, message7, sizeof(message7), init_value, crc_xor_value,
                            true, true, true));
}

TEST(Crc32, CRC32Base_Reflect_input) {
    TEST_ASSERT_EQUAL_HEX32(0x38FB2284U, Crc32Base(crc32_table, message1, sizeof(message1), init_value, crc_xor_value,
                            false, true, true));
    TEST_ASSERT_EQUAL_HEX32(0xEEB9D524U, Crc32Base(crc32_table, message2, sizeof(message2), init_value, crc_xor_value,
                            false, true, true));
    TEST_ASSERT_EQUAL_HEX32(0xE14D936DU, Crc32Base(crc32_table, message3, sizeof(message3), init_value, crc_xor_value,
                            false, true, true));
    TEST_ASSERT_EQUAL_HEX32(0x4846054CU, Crc32Base(crc32_table, message4, sizeof(message4), init_value, crc_xor_value,
                            false, true, true));
    TEST_ASSERT_EQUAL_HEX32(0xBC61750DU, Crc32Base(crc32_table, message5, sizeof(message5), init_value, crc_xor_value,
                            false, true, true));
    TEST_ASSERT_EQUAL_HEX32(0xD9457B39U, Crc32Base(crc32_table, message6, sizeof(message6), init_value, crc_xor_value,
                            false, true, true));
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFFFFU, Crc32Base(crc32_table, message7, sizeof(message7), init_value, crc_xor_value,
                            false, true, true));
}

TEST(Crc32, CRC32Base_Reflect_output) {
    TEST_ASSERT_EQUAL_HEX32(0x2144DF1CU, Crc32Base(crc32_table, message1, sizeof(message1), init_value, crc_xor_value,
                            true, false, true));
    TEST_ASSERT_EQUAL_HEX32(0x53677982U, Crc32Base(crc32_table, message2, sizeof(message2), init_value, crc_xor_value,
                            true, false, true));
    TEST_ASSERT_EQUAL_HEX32(0xFB566F16U, Crc32Base(crc32_table, message3, sizeof(message3), init_value, crc_xor_value,
                            true, false, true));
    TEST_ASSERT_EQUAL_HEX32(0x2857B480U, Crc32Base(crc32_table, message4, sizeof(message4), init_value, crc_xor_value,
                            true, false, true));
    TEST_ASSERT_EQUAL_HEX32(0xBD39C06BU, Crc32Base(crc32_table, message5, sizeof(message5), init_value, crc_xor_value,
                            true, false, true));
    TEST_ASSERT_EQUAL_HEX32(0x616B4732U, Crc32Base(crc32_table, message6, sizeof(message6), init_value, crc_xor_value,
                            true, false, true));
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFFFFU, Crc32Base(crc32_table, message7, sizeof(message7), init_value, crc_xor_value,
                            true, false, true));
}

TEST(Crc32, CRC32Base_Without_finish_xor) {
    TEST_ASSERT_EQUAL_HEX32(0xDEBB20E3U, Crc32Base(crc32_table, message1, sizeof(message1), init_value, crc_xor_value,
                            true, true, false));
    TEST_ASSERT_EQUAL_HEX32(0xDB546288U, Crc32Base(crc32_table, message2, sizeof(message2), init_value, crc_xor_value,
                            true, true, false));
    TEST_ASSERT_EQUAL_HEX32(0x49364D78U, Crc32Base(crc32_table, message3, sizeof(message3), init_value, crc_xor_value,
                            true, true, false));
    TEST_ASSERT_EQUAL_HEX32(0xCD5F9DEDU, Crc32Base(crc32_table, message4, sizeof(message4), init_value, crc_xor_value,
                            true, true, false));
    TEST_ASSERT_EQUAL_HEX32(0x4F5179C2U, Crc32Base(crc32_table, message5, sizeof(message5), init_value, crc_xor_value,
                            true, true, false));
    TEST_ASSERT_EQUAL_HEX32(0x63215D64U, Crc32Base(crc32_table, message6, sizeof(message6), init_value, crc_xor_value,
                            true, true, false));
    TEST_ASSERT_EQUAL_HEX32(0x00000000U, Crc32Base(crc32_table, message7, sizeof(message7), init_value, crc_xor_value,
                            true, true, false));
}

TEST(Crc32, Crc32) {
    TEST_ASSERT_EQUAL_HEX32(0x2144DF1CU, Crc32(message1, sizeof(message1), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x24AB9D77U, Crc32(message2, sizeof(message2), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0xB6C9B287U, Crc32(message3, sizeof(message3), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x32A06212U, Crc32(message4, sizeof(message4), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0xB0AE863DU, Crc32(message5, sizeof(message5), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x9CDEA29BU, Crc32(message6, sizeof(message6), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFFFFU, Crc32(message7, sizeof(message7), true, NULL_PTR));

    // Test with message in chunks
    uint32_t crc_result = Crc32(&message5[0], 2U, false, NULL_PTR);
    crc_result = Crc32(&message5[2], 5U, false, &crc_result);
    crc_result = Crc32(&message5[7], 2U, true, &crc_result);
    TEST_ASSERT_EQUAL_HEX32(0xB0AE863DU, crc_result);
}

TEST(Crc32, Crc32_bzip2) {
    TEST_ASSERT_EQUAL_HEX32(0x38FB2284U, Crc32_bzip2(message1, sizeof(message1), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x419EE6CAU, Crc32_bzip2(message2, sizeof(message2), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x68F66ADFU, Crc32_bzip2(message3, sizeof(message3), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x012DEA14U, Crc32_bzip2(message4, sizeof(message4), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0xD6039CBDU, Crc32_bzip2(message5, sizeof(message5), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x4CE2D686U, Crc32_bzip2(message6, sizeof(message6), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFFFFU, Crc32_bzip2(message7, sizeof(message7), true, NULL_PTR));

    // Test with message in chunks
    uint32_t crc_result = Crc32_bzip2(&message5[0], 2U, false, NULL_PTR);
    crc_result = Crc32_bzip2(&message5[2], 5U, false, &crc_result);
    crc_result = Crc32_bzip2(&message5[7], 2U, true, &crc_result);
    TEST_ASSERT_EQUAL_HEX32(0xD6039CBDU, crc_result);
}

TEST(Crc32, Crc32_c) {
    TEST_ASSERT_EQUAL_HEX32(0x48674BC7U, Crc32_c(message1, sizeof(message1), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x70ABD088U, Crc32_c(message2, sizeof(message2), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0xDEAABEBBU, Crc32_c(message3, sizeof(message3), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0xA6ADEA2DU, Crc32_c(message4, sizeof(message4), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0xB59CA09BU, Crc32_c(message5, sizeof(message5), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x99357B56U, Crc32_c(message6, sizeof(message6), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFFFFU, Crc32_c(message7, sizeof(message7), true, NULL_PTR));

    // Test with message in chunks
    uint32_t crc_result = Crc32_c(&message5[0], 2U, false, NULL_PTR);
    crc_result = Crc32_c(&message5[2], 5U, false, &crc_result);
    crc_result = Crc32_c(&message5[7], 2U, true, &crc_result);
    TEST_ASSERT_EQUAL_HEX32(0xB59CA09BU, crc_result);
}

TEST(Crc32, Crc32_d) {
    TEST_ASSERT_EQUAL_HEX32(0xBAD8FAAEU, Crc32_d(message1, sizeof(message1), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x001A059CU, Crc32_d(message2, sizeof(message2), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x1A266FFAU, Crc32_d(message3, sizeof(message3), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0xC636481BU, Crc32_d(message4, sizeof(message4), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0xCF0E6328U, Crc32_d(message5, sizeof(message5), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x4B92ADBEU, Crc32_d(message6, sizeof(message6), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFFFFU, Crc32_d(message7, sizeof(message7), true, NULL_PTR));

    // Test with message in chunks
    uint32_t crc_result = Crc32_d(&message5[0], 2U, false, NULL_PTR);
    crc_result = Crc32_d(&message5[2], 5U, false, &crc_result);
    crc_result = Crc32_d(&message5[7], 2U, true, &crc_result);
    TEST_ASSERT_EQUAL_HEX32(0xCF0E6328U, crc_result);
}

TEST(Crc32, Crc32_jamcrc) {
    TEST_ASSERT_EQUAL_HEX32(0xDEBB20E3U, Crc32_jamcrc(message1, sizeof(message1), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0xDB546288U, Crc32_jamcrc(message2, sizeof(message2), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x49364D78U, Crc32_jamcrc(message3, sizeof(message3), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0xCD5F9DEDU, Crc32_jamcrc(message4, sizeof(message4), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x4F5179C2U, Crc32_jamcrc(message5, sizeof(message5), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x63215D64U, Crc32_jamcrc(message6, sizeof(message6), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x00000000U, Crc32_jamcrc(message7, sizeof(message7), true, NULL_PTR));

    // Test with message in chunks
    uint32_t crc_result = Crc32_jamcrc(&message5[0], 2U, false, NULL_PTR);
    crc_result = Crc32_jamcrc(&message5[2], 5U, false, &crc_result);
    crc_result = Crc32_jamcrc(&message5[7], 2U, true, &crc_result);
    TEST_ASSERT_EQUAL_HEX32(0x4F5179C2U, crc_result);
}

TEST(Crc32, Crc32_mpeg2) {
    TEST_ASSERT_EQUAL_HEX32(0xC704DD7BU, Crc32_mpeg2(message1, sizeof(message1), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0xBE611935U, Crc32_mpeg2(message2, sizeof(message2), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x97099520U, Crc32_mpeg2(message3, sizeof(message3), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0xFED215EBU, Crc32_mpeg2(message4, sizeof(message4), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x29FC6342U, Crc32_mpeg2(message5, sizeof(message5), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0xB31D2979U, Crc32_mpeg2(message6, sizeof(message6), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x00000000U, Crc32_mpeg2(message7, sizeof(message7), NULL_PTR));

    // Test with message in chunks
    uint32_t crc_result = Crc32_mpeg2(&message5[0], 2U, NULL_PTR);
    crc_result = Crc32_mpeg2(&message5[2], 5U, &crc_result);
    crc_result = Crc32_mpeg2(&message5[7], 2U, &crc_result);
    TEST_ASSERT_EQUAL_HEX32(0x29FC6342U, crc_result);
}

TEST(Crc32, Crc32_posix) {
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFFFFU, Crc32_posix(message1, sizeof(message1), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0xF6FA9BCAU, Crc32_posix(message2, sizeof(message2), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0xAFF2B7A4U, Crc32_posix(message3, sizeof(message3), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0xC629376FU, Crc32_posix(message4, sizeof(message4), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x5CD4F325U, Crc32_posix(message5, sizeof(message5), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0xFB86AB86U, Crc32_posix(message6, sizeof(message6), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x38FB2284U, Crc32_posix(message7, sizeof(message7), true, NULL_PTR));

    // Test with message in chunks
    uint32_t crc_result = Crc32_posix(&message5[0], 2U, false, NULL_PTR);
    crc_result = Crc32_posix(&message5[2], 5U, false, &crc_result);
    crc_result = Crc32_posix(&message5[7], 2U, true, &crc_result);
    TEST_ASSERT_EQUAL_HEX32(0x5CD4F325U, crc_result);
}

TEST(Crc32, Crc32_q) {
    TEST_ASSERT_EQUAL_HEX32(0x00000000U, Crc32_q(message1, sizeof(message1), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x09F26687U, Crc32_q(message2, sizeof(message2), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x2C8E43FCU, Crc32_q(message3, sizeof(message3), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0xA854EA7CU, Crc32_q(message4, sizeof(message4), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x64E7EA17U, Crc32_q(message5, sizeof(message5), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x35BD0C6CU, Crc32_q(message6, sizeof(message6), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x90A54352U, Crc32_q(message7, sizeof(message7), NULL_PTR));

    // Test with message in chunks
    uint32_t crc_result = Crc32_q(&message5[0], 2U, NULL_PTR);
    crc_result = Crc32_q(&message5[2], 5U, &crc_result);
    crc_result = Crc32_q(&message5[7], 2U, &crc_result);
    TEST_ASSERT_EQUAL_HEX32(0x64E7EA17U, crc_result);
}

TEST(Crc32, Crc32_xfer) {
    TEST_ASSERT_EQUAL_HEX32(0x00000000U, Crc32_xfer(message1, sizeof(message1), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x620EF971U, Crc32_xfer(message2, sizeof(message2), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x734620C1U, Crc32_xfer(message3, sizeof(message3), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x6546295FU, Crc32_xfer(message4, sizeof(message4), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0xD543C03CU, Crc32_xfer(message5, sizeof(message5), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x5C148A23U, Crc32_xfer(message6, sizeof(message6), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX32(0x00003C56U, Crc32_xfer(message7, sizeof(message7), NULL_PTR));

    // Test with message in chunks
    uint32_t crc_result = Crc32_xfer(&message5[0], 2U, NULL_PTR);
    crc_result = Crc32_xfer(&message5[2], 5U, &crc_result);
    crc_result = Crc32_xfer(&message5[7], 2U, &crc_result);
    TEST_ASSERT_EQUAL_HEX32(0xD543C03CU, crc_result);
}
