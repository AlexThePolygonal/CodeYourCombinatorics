#pragma once
#include "niceties.hpp"
#include <vector>
#include <array>
#include <fstream>
#include <cstring>
#include <iostream>

namespace primes {
    const std::vector<u_int64_t> bertrand_primes = {
        2, 3, 5, 7, 13, 23, 43, 83, 163, 317, 631, 1259, 2503, 5003, 9973, 19937, 39869, 79699, 159389, 318751, 637499, 1274989, 2549951, 5099893, 10199767, 20399531, 40799041, 81598067, 163196129, 326392249, 652784471, 1305568919, 2611137817, 5222275627,10444551233, 20889102457, 41778204911,83556409789,167112819547,334225639093,668451278147,1336902556279,2673805112521,5347610225021,10695220450027,21390440900033,42780881800057,85561763600057,171123527200081,342247054400159,684494108800091,1368988217600167,2737976435200319,5475952870400627,10951905740801243,21903811481602373,43807622963204729,87615245926409407,175230491852818793,350460983705637557,700921967411275081,1401843934822550129,2803687869645100253,5607375739290200429,11214751478580400831u
    };

    template <class Scalar>
    std::vector<bool> eratosthenes_sieve(Scalar n) {
        std::vector<bool> sieve(n+1, true);
        sieve[0] = false;
        sieve[1] = false;
        Scalar i = 2;
        while (i * i <= n) {
            if (sieve[i]) {  
                Scalar j = i * i;
                while (j <= n) {
                    sieve[j] = false;
                    j += i;
                }
            }
            i++;
        }
        return sieve;
    }

    // loads precomputed primes from a binary file
    std::vector<uint32_t> precomputed_primes(std::string path = "primes32/primes.32b", size_t prime_cnt = 203280220) {
        std::ifstream input(path, std::ios::binary);
        char* rawmem = new char[prime_cnt*4];
        std::vector<uint32_t> res(prime_cnt, 0);
        input.read(rawmem, prime_cnt*4);

        std::memcpy(res.data(), rawmem, prime_cnt*4);
        delete[] rawmem;
        return res;
    }
};