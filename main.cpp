#include <iostream>
#include <vector>
#include <string>
//#include <сstring>
#include <fstream>
#include <sstream>

using namespace std;

struct Record {
    uint32_t freq;
    uint32_t group;
    uint32_t cc;
    vector<uint8_t> key;
};

bool record_is_equal(const Record &a, const Record &b)
{
    return a.freq == b.freq && a.group == b.group && a.cc == b.cc && a.key == b.key;
}

void compute_tabular_method_tables_reverse(uint32_t* pTbl, uint32_t kNumTables)
{
    uint32_t i = 0;
    uint32_t PP = 0x04C11DB7;

    // initialize tbl0, the first 256 elements of pTbl,
    // using naive CRC to compute pTbl[i] = CRC(i)
    for (; i < 256; ++i) {
        uint32_t R = i << 24;
        for (int j = 0; j < 8; ++j)
            R = R & (1L<<31) ? (R << 1) ^ PP : R << 1;
        pTbl[i] = R;
    }

    // initialize remaining tables by taking the previous
    // table's entry for i and churning through 8 more zero bits
    for (; i < kNumTables * 256; ++i) {
        const uint32_t R = pTbl[i - 256];
        pTbl[i] = (R << 8) ^ pTbl[(uint8_t)(R>>24)];
    }
}

vector<uint8_t> trans(const string str)
{
    vector<uint8_t> res(str.length()/2);
    char tmp[3] = {0, 0, 0};
    for (int i=0;i<str.length()/2;i++) {
        tmp[0] = str[2*i];
        tmp[1] = str[2*i+1];
        res[i] = strtol(tmp, NULL, 16) & 0xff;
    }
    return res;
}

uint32_t g_tbl_R[256*12];

static uint32_t crc32_12_bytes(const uint8_t *M)
{
    uint32_t R = 0;
    R ^= M[0]|(M[1]<<8)|(M[2]<<16)|(M[3]<<24);
    R = g_tbl_R[ 0 * 256 + M[11]] ^
    g_tbl_R[ 1 * 256 + M[10]] ^
    g_tbl_R[ 2 * 256 + M[9]] ^
    g_tbl_R[ 3 * 256 + M[8]] ^
    g_tbl_R[ 4 * 256 + M[7]] ^
    g_tbl_R[ 5 * 256 + M[6]] ^
    g_tbl_R[ 6 * 256 + M[5]] ^
    g_tbl_R[ 7 * 256 + M[4]] ^
    g_tbl_R[ 8 * 256 + M[3]] ^
    g_tbl_R[ 9 * 256 + M[2]] ^
    g_tbl_R[10 * 256 + M[1]] ^
    g_tbl_R[11 * 256 + M[0]];
    return R;
}

uint8_t md680_alg1_tbl[256];

static void md680_alg1_init(uint8_t *in, uint8_t len)
{
    for (int i=0;i<256;i++)
        md680_alg1_tbl[i] = i;
    
    uint8_t k8 = 0;
    for (int i=0;i<256;i++) {
        k8 = (md680_alg1_tbl[i] + k8 +in[i%len]) & 0xff;
        uint8_t t9 = md680_alg1_tbl[i];
        md680_alg1_tbl[i] = md680_alg1_tbl[k8];
        md680_alg1_tbl[k8] = t9;
    }
}


static void md680_make_key(vector<uint8_t> &key, vector<uint8_t> &iv)
{
    uint8_t md680_kiv[16];
    
    for (int i=0;i<6;i++)
        md680_kiv[2*i+1] = iv[i];
    
    
    for (int i=0;i<6;i++)
        md680_kiv[2*i+0] = key[i];
    
    uint32_t crc = crc32_12_bytes(md680_kiv);
    //        uint32_t crc = crc32_12_bytes_reverse(md680_kiv);
    md680_kiv[12] = crc & 0xff;
    md680_kiv[13] = (crc >> 8) & 0xff;
    md680_kiv[14] = (crc >> 16) & 0xff;
    md680_kiv[15] = (crc >> 24) & 0xff;
    
    md680_alg1_init(md680_kiv, sizeof(md680_kiv));
}

static void md680_decrypt_alg1(uint8_t *buf, uint8_t len)
{
        uint8_t *tbl;
        uint8_t j = 0;
        uint8_t k = 0;

        tbl = md680_alg1_tbl;
        for (int i=0;i<len;i++) {
                j += 1;
                k = k + tbl[j];
                uint8_t a = tbl[j];
                tbl[j] = tbl[k];
                tbl[k] = a;
                uint8_t b = (tbl[k] + tbl[j]) & 0xff;
                buf[i] ^= tbl[b];
        }
}

uint32_t target = 0xcc8cc000;


int main() {
    fstream records_in("keys.txt", records_in.in);
    vector<Record> records;
    string line;
    while (getline(records_in, line)) {
        Record rec;
        
        int found = line.find_first_of(" ");
        rec.freq = stoi(line.substr(0, found));
        
        found = line.find_first_of(" ",found+1);
        found = line.find_first_of(" ",found+1);
        
        rec.group = stoi(line.substr(found+1, line.find_first_of(" ",found+1)-found-1));
        found = line.find_first_of(" ",found+1);
        
        rec.cc = stoi(line.substr(found+1, line.find_first_of(" ",found+1)-found-1));
        found = line.find_first_of(" ",found+1);
        
        rec.key = trans(line.substr(found+1));
        cout<<line.substr(found+1)<<'\n';
        
        records.push_back(rec);
    }
    
    compute_tabular_method_tables_reverse(g_tbl_R, 12);
    vector<vector<uint8_t> > keys;
    
    fstream keys_in("keys680.txt", keys_in.in);
//    ifstream keys_in("keys680.txt");
//    if(!keys_in.is_open()) {
//        cout<<"AAAAAA\n";
//    }
    while (getline(keys_in, line)) {
        keys.push_back(trans(line));
    }
    
    
//    for (auto k:keys) {
//        for (int i=0;i<6;++i)
//            cout<<k[i]<<' ';
//        cout<<'\n';
//    }
    
//   cout<<"Done1\n\n";
    
    // vector<vector<uint8_t> > dumps;
    
    FILE * records_file = fopen("keys.txt", "a");
    
    fstream dump_in("dump680.txt", dump_in.in);
//    fstream keys_out("dump680.txt", keys_out.out);
    while (getline(dump_in, line)) {
//        cout<<line<<'\n';
        Record rec;
        vector<uint8_t> iv;
    
        unsigned long found = line.find_first_of(" ");
        rec.freq = stoi(line.substr(0, found));
        
        iv = trans(line.substr(found+1, line.find_first_of(" ",found+1)-found-1));
        found = line.find_first_of(" ",found+1);
        
        rec.group = stoi(line.substr(found+1, line.find_first_of(" ",found+1)-found-1));
        found = line.find_first_of(" ",found+1);
        
        rec.cc = stoi(line.substr(found));
//        
//        cout<<rec.freq<<'\n';
//        for (int i=0;i<6;++i)
//            cout<<rec.iv[i]<<' ';
//        cout<<'\n';
//        cout<<rec.group<<' '<<rec.cc<<'\n'<<'\n';
        
        //records.push_back(rec);
        
        
        getline(dump_in, line);
        uint8_t dump[27];
        vector<uint8_t> tmp = trans(line);
        for (int i=0;i<27;++i)
            dump[i] = tmp[i];
        //dumps.push_back(trans(line));
        
        if ((dump[5] & 0x88) == 0x08 && (dump[6] & 0x88) == 0x80 &&
            (dump[7] & 0x88) == 0x08 && (dump[8] & 0x88) == 0x80 &&
            (dump[15] & 0x88) == 0x80 &&
            (dump[16] & 0x88) == 0x08 && (dump[17] & 0x88) == 0x80 &&
            (dump[24] & 0x88) == 0x80 &&
            (dump[25] & 0x88) == 0x08 && (dump[26] & 0x88) == 0x80) {
            target = 0xc888c400;
//            printf("good1\n");
        }

        if ((dump[5] & 0x88) == 0x80 && (dump[6] & 0x88) == 0x80 &&
            (dump[7] & 0x88) == 0x00 && (dump[8] & 0x88) == 0x08 &&
            (dump[15] & 0x88) == 0x80 &&
            (dump[16] & 0x88) == 0x00 && (dump[17] & 0x88) == 0x08 &&
            (dump[24] & 0x88) == 0x80 &&
            (dump[25] & 0x88) == 0x00 && (dump[26] & 0x88) == 0x08) {
            target = 0xcc8cc000;
//            printf("good2\n");
        }
        
        uint8_t to_decrypt[16];
        memcpy(to_decrypt, dump, 5);
        memcpy(to_decrypt+5, dump+9, 5);
        memcpy(to_decrypt+10, dump+18, 5);
        to_decrypt[15] = (dump[14] &0xf0) | (dump[23] >> 4);
        
        for (auto key:keys) {
            uint8_t to_decrypt_cp[16];
            memcpy(to_decrypt_cp, to_decrypt, 16);
            
            md680_make_key(key, iv);
            md680_decrypt_alg1(to_decrypt_cp, 16);
//            for (int i=0;i<16;++i) {
//                printf("%02X ", to_decrypt_cp[i]);
//            }
//            cout<<'\n';
            
            int cnt = 0;
            
            for (int i=0;i<3;i++) {
                uint32_t v = ((to_decrypt_cp[i*5+0] & 0xcc) << 24) |
                    ((to_decrypt_cp[i*5+1] & 0xcc) << 16) |
                    ((to_decrypt_cp[i*5+2] & 0xcc) <<  8) |
                    ((to_decrypt_cp[i*5+3] & 0x88))       |
                    ((to_decrypt_cp[i*5+4] & 0x88) >>  1);
                if (v == target) {
//                    cout<<"Yes\n";
                    ++cnt;
                }
#if 0
                printf("%02x %02x %02x ",
                    buf[i*5] & 0xcc, buf[i*5+1] & 0xcc,
                    buf[i*5+2] & 0xcc);
#endif
            }
            if (cnt == 3) {
                printf("%d 44 000 %04d %02d ", rec.freq, rec.group, rec.cc);
                for (auto x:key)
                    printf("%02x", x);
                printf("\n");
                rec.key = key;
                
                bool flag = true;
                for (auto record:records)
                    if (record_is_equal(rec, record))
                        flag = false;
                
                if (flag) {
                    records.push_back(rec);
                    fprintf(records_file, "\n%d 44 000 %04d %02d ", rec.freq, rec.group, rec.cc);
                    for (auto x:key)
                        fprintf(records_file, "%02x", x);
                }
            }
        }
        
//        cout<<'\n';
    }
    

//    for (auto d:dumps) {
//        for (int i=0;i<27;++i)
//            cout<<d[i]<<' ';
//        cout<<'\n';
//    }
    
    return 0;
}
