#define _CRT_SECURE_NO_WARNINGS
#include <iostream>     // std::cout, std::fixed(no longer used)
#include <fstream> //ofstream, ifstream (input/output from file)
using namespace std;

//Provided Functions
	int md5Hash(const char account_no[], char md5_hash_account_no[], int size_of_hash);
	int CreateNewAccountFile(const char account_no[]);
	int Encrypt(const char account_no[], const char passphrase[]);
	int Decrypt(const char account_no[], const char passphrase[]);
//End of Provided Functions

//Required Functions to Implement
	bool makeDeposit(const char account_no[], const char passphrase[], double amount);  
	bool makeWithdrawal(const char account_no[], const char passphrase[], double amount);  
	double getBalance(const char account_no[], const char passphrase[]);
	bool addNewAccount();
	void printTopNTransactions(const char account_no[], const char passphrase[], int n);
	bool createLogFile();
//End of Required Functions to Implement

int main()
{
	return 0;
}

/*
*	It first checks if amount is in the proper amount format
*	(e.g., 57.20, 90, 120.41),if it is not it returns false. 
*	It makes a deposit of amount to the account (i.e., 
*	appends amount to the account file).
*/
bool makeDeposit(const char account_no[], const char passphrase[], double amount)
{
	return false;
}

/*
*	It first checks if amount is in the proper amount format
*	(e.g., 57.20, 90, 120.41), if it is not it returns false. 
*	It checks if amount is less than or equal to balance 
*	before making the withdrawal. If there is insufficient 
*	amount in the account to make the withdrawal, it will log 
*	a proper message and charges $10 overdraft penalty fee to 
*	the account, without making the requested withdrawal.
*/
bool makeWithdraw(const char account_no[], const char passphrase[], double amount)
{
	return false;
}

/*
*	For the particular bank account (account_no), this 
*	function calculates the account balance by summing all 
*	the deposits and withdrawals in the transaction history 
*	for that particular bank account. For instance, for the 
*	example provided the function will return 10 because 
*	0+20+100-10+100-200=10.
*/
double getBalance(const char account_no[], const char passphrase[])
{
	return 0.0;
}

/*
*	This function returns the n transactions with highest 
*	amount from the last 1000 transactions (whether they 
*	are deposits or withdraws). If n is greater than the 
*	number of transactions it will return all transactions 
*	recorded in the account transaction history.
*
*	For example, executing printTopNTransactions("12345-67890", 3) would output: 
*	-200
*	100
*	100
*/
void printTopNTransactions(const char account_no[], const char passphrase[], int n)
{
	return;
}

/*
*	Upon calling this function it will ask the user the necessary information to open up an account.
*	The newly created account will be encrypted before returning the function.
*	Your function will technically do the following in the order provided. 
*
*	- Ask user for the account number
*	- Checks if the entered bank account is valid otherwise it should return false
*	(i.e. it is in the following format: XXXXX-XXXXX) 
*	(we recommend creating a function called isValidAccountNumber(const char account_no[])) to check for that)
*	- Ask user for the passphrase that will be associated to the account number
*	- Ask user for the account holder's personal information
*	- Call CreateNewAccountFile(account_no)
*	- Add the account holder personal information in one line to the file
*	- Add 0 to the file in the second line to represent the initial transaction amount
*	- Encrypt file using passphrase
*/
bool addNewAccount(const char account_no[], const char passphrase[])
{
	return false;
}

/*
	Function "log" appends to the log file any message of size up to 100. 
	Note that the if the file doesn't exist it will create it. Steps:
    1. open the log file for appending (return false if failed)
    2. add a simple timestamp preceding each log entry
    3. append the massage to the log file(one line for each log message)
    4. return true
*/
bool log(FILE*, const char log_message)
{
	return false;
}


/**************************************************************************************************************************************************************
***DO_NOT_TOUCH____PROVIDED_FUNCTION_IMPLEMENTATION____DO_NOT_TOUCH____PROVIDED_FUNCTION_IMPLEMENTATION____DO_NOT_TOUCH____PROVIDED_FUNCTION_IMPLEMENTATION****
**************************************************************************************************************************************************************/

#ifndef ENCRYPT_DECRYPT_DO_NOT_TOUCH
#define _CRT_SECURE_NO_WARNINGS

/*  
*   Byte-oriented AES-256 implementation.
*   All lookup tables replaced with 'on the fly' calculations. 
*
*   Copyright (c) 2007-2009 Ilya O. Levin, http://www.literatecode.com
*   Other contributors: Hal Finney
*
*   Permission to use, copy, modify, and distribute this software for any
*   purpose with or without fee is hereby granted, provided that the above
*   copyright notice and this permission notice appear in all copies.
*
*   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
*   WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
*   MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
*   ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
*   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
*   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
*   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
#ifndef uint8_t
#define uint8_t  unsigned char
#endif

#ifdef __cplusplus
extern "C" { 
#endif

	typedef struct {
		uint8_t key[32]; 
		uint8_t enckey[32]; 
		uint8_t deckey[32];
	} aes256_context; 


	void aes256_init(aes256_context *, uint8_t * /* key */);
	void aes256_done(aes256_context *);
	void aes256_encrypt_ecb(aes256_context *, uint8_t * /* plaintext */);
	void aes256_decrypt_ecb(aes256_context *, uint8_t * /* cipertext */);

#ifdef __cplusplus
}
#endif

#define F(x)   (((x)<<1) ^ ((((x)>>7) & 1) * 0x1b))
#define FD(x)  (((x) >> 1) ^ (((x) & 1) ? 0x8d : 0))

// #define BACK_TO_TABLES
#ifdef BACK_TO_TABLES

const uint8_t sbox[256] = {
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
	0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
	0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc,
	0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a,
	0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
	0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b,
	0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85,
	0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
	0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17,
	0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88,
	0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
	0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9,
	0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6,
	0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
	0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94,
	0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68,
	0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};
const uint8_t sboxinv[256] = {
	0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38,
	0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
	0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87,
	0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
	0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d,
	0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
	0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2,
	0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
	0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16,
	0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
	0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda,
	0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
	0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a,
	0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
	0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02,
	0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
	0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea,
	0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
	0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85,
	0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
	0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89,
	0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
	0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20,
	0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
	0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31,
	0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
	0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d,
	0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
	0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0,
	0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
	0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26,
	0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};

#define rj_sbox(x)     sbox[(x)]
#define rj_sbox_inv(x) sboxinv[(x)]

#else /* tableless subroutines */

/* -------------------------------------------------------------------------- */
uint8_t gf_alog(uint8_t x) // calculate anti-logarithm gen 3
{
	uint8_t atb = 1, z;

	while (x--) {z = atb; atb <<= 1; if (z & 0x80) atb^= 0x1b; atb ^= z;}

	return atb;
} /* gf_alog */

/* -------------------------------------------------------------------------- */
uint8_t gf_log(uint8_t x) // calculate logarithm gen 3
{
	uint8_t atb = 1, i = 0, z;

	do {
		if (atb == x) break;
		z = atb; atb <<= 1; if (z & 0x80) atb^= 0x1b; atb ^= z;
	} while (++i > 0);

	return i;
} /* gf_log */


/* -------------------------------------------------------------------------- */
uint8_t gf_mulinv(uint8_t x) // calculate multiplicative inverse
{
	return (x) ? gf_alog(255 - gf_log(x)) : 0;
} /* gf_mulinv */

/* -------------------------------------------------------------------------- */
uint8_t rj_sbox(uint8_t x)
{
	uint8_t y, sb;

	sb = y = gf_mulinv(x);
	y = (y<<1)|(y>>7); sb ^= y;  y = (y<<1)|(y>>7); sb ^= y; 
	y = (y<<1)|(y>>7); sb ^= y;  y = (y<<1)|(y>>7); sb ^= y;

	return (sb ^ 0x63);
} /* rj_sbox */

/* -------------------------------------------------------------------------- */
uint8_t rj_sbox_inv(uint8_t x)
{
	uint8_t y, sb;

	y = x ^ 0x63;
	sb = y = (y<<1)|(y>>7);
	y = (y<<2)|(y>>6); sb ^= y; y = (y<<3)|(y>>5); sb ^= y;

	return gf_mulinv(sb);
} /* rj_sbox_inv */

#endif

/* -------------------------------------------------------------------------- */
uint8_t rj_xtime(uint8_t x) 
{
	return (x & 0x80) ? ((x << 1) ^ 0x1b) : (x << 1);
} /* rj_xtime */

/* -------------------------------------------------------------------------- */
void aes_subBytes(uint8_t *buf)
{
	register uint8_t i = 16;

	while (i--) buf[i] = rj_sbox(buf[i]);
} /* aes_subBytes */

/* -------------------------------------------------------------------------- */
void aes_subBytes_inv(uint8_t *buf)
{
	register uint8_t i = 16;

	while (i--) buf[i] = rj_sbox_inv(buf[i]);
} /* aes_subBytes_inv */

/* -------------------------------------------------------------------------- */
void aes_addRoundKey(uint8_t *buf, uint8_t *key)
{
	register uint8_t i = 16;

	while (i--) buf[i] ^= key[i];
} /* aes_addRoundKey */

/* -------------------------------------------------------------------------- */
void aes_addRoundKey_cpy(uint8_t *buf, uint8_t *key, uint8_t *cpk)
{
	register uint8_t i = 16;

	while (i--)  buf[i] ^= (cpk[i] = key[i]), cpk[16+i] = key[16 + i];
} /* aes_addRoundKey_cpy */


/* -------------------------------------------------------------------------- */
void aes_shiftRows(uint8_t *buf)
{
	register uint8_t i, j; /* to make it potentially parallelable :) */

	i = buf[1]; buf[1] = buf[5]; buf[5] = buf[9]; buf[9] = buf[13]; buf[13] = i;
	i = buf[10]; buf[10] = buf[2]; buf[2] = i;
	j = buf[3]; buf[3] = buf[15]; buf[15] = buf[11]; buf[11] = buf[7]; buf[7] = j;
	j = buf[14]; buf[14] = buf[6]; buf[6]  = j;

} /* aes_shiftRows */

/* -------------------------------------------------------------------------- */
void aes_shiftRows_inv(uint8_t *buf)
{
	register uint8_t i, j; /* same as above :) */

	i = buf[1]; buf[1] = buf[13]; buf[13] = buf[9]; buf[9] = buf[5]; buf[5] = i;
	i = buf[2]; buf[2] = buf[10]; buf[10] = i;
	j = buf[3]; buf[3] = buf[7]; buf[7] = buf[11]; buf[11] = buf[15]; buf[15] = j;
	j = buf[6]; buf[6] = buf[14]; buf[14] = j;

} /* aes_shiftRows_inv */

/* -------------------------------------------------------------------------- */
void aes_mixColumns(uint8_t *buf)
{
	register uint8_t i, a, b, c, d, e;

	for (i = 0; i < 16; i += 4)
	{
		a = buf[i]; b = buf[i + 1]; c = buf[i + 2]; d = buf[i + 3];
		e = a ^ b ^ c ^ d;
		buf[i] ^= e ^ rj_xtime(a^b);   buf[i+1] ^= e ^ rj_xtime(b^c);
		buf[i+2] ^= e ^ rj_xtime(c^d); buf[i+3] ^= e ^ rj_xtime(d^a);
	}
} /* aes_mixColumns */

/* -------------------------------------------------------------------------- */
void aes_mixColumns_inv(uint8_t *buf)
{
	register uint8_t i, a, b, c, d, e, x, y, z;

	for (i = 0; i < 16; i += 4)
	{
		a = buf[i]; b = buf[i + 1]; c = buf[i + 2]; d = buf[i + 3];
		e = a ^ b ^ c ^ d;
		z = rj_xtime(e);
		x = e ^ rj_xtime(rj_xtime(z^a^c));  y = e ^ rj_xtime(rj_xtime(z^b^d));
		buf[i] ^= x ^ rj_xtime(a^b);   buf[i+1] ^= y ^ rj_xtime(b^c);
		buf[i+2] ^= x ^ rj_xtime(c^d); buf[i+3] ^= y ^ rj_xtime(d^a);
	}
} /* aes_mixColumns_inv */

/* -------------------------------------------------------------------------- */
void aes_expandEncKey(uint8_t *k, uint8_t *rc) 
{
	register uint8_t i;

	k[0] ^= rj_sbox(k[29]) ^ (*rc);
	k[1] ^= rj_sbox(k[30]);
	k[2] ^= rj_sbox(k[31]);
	k[3] ^= rj_sbox(k[28]);
	*rc = F( *rc);

	for(i = 4; i < 16; i += 4)  k[i] ^= k[i-4],   k[i+1] ^= k[i-3],
		k[i+2] ^= k[i-2], k[i+3] ^= k[i-1];
	k[16] ^= rj_sbox(k[12]);
	k[17] ^= rj_sbox(k[13]);
	k[18] ^= rj_sbox(k[14]);
	k[19] ^= rj_sbox(k[15]);

	for(i = 20; i < 32; i += 4) k[i] ^= k[i-4],   k[i+1] ^= k[i-3],
		k[i+2] ^= k[i-2], k[i+3] ^= k[i-1];

} /* aes_expandEncKey */

/* -------------------------------------------------------------------------- */
void aes_expandDecKey(uint8_t *k, uint8_t *rc) 
{
	uint8_t i;

	for(i = 28; i > 16; i -= 4) k[i+0] ^= k[i-4], k[i+1] ^= k[i-3], 
		k[i+2] ^= k[i-2], k[i+3] ^= k[i-1];

	k[16] ^= rj_sbox(k[12]);
	k[17] ^= rj_sbox(k[13]);
	k[18] ^= rj_sbox(k[14]);
	k[19] ^= rj_sbox(k[15]);

	for(i = 12; i > 0; i -= 4)  k[i+0] ^= k[i-4], k[i+1] ^= k[i-3],
		k[i+2] ^= k[i-2], k[i+3] ^= k[i-1];

	*rc = FD(*rc);
	k[0] ^= rj_sbox(k[29]) ^ (*rc);
	k[1] ^= rj_sbox(k[30]);
	k[2] ^= rj_sbox(k[31]);
	k[3] ^= rj_sbox(k[28]);
} /* aes_expandDecKey */


/* -------------------------------------------------------------------------- */
void aes256_init(aes256_context *ctx, uint8_t *k)
{
	uint8_t rcon = 1;
	register uint8_t i;

	for (i = 0; i < sizeof(ctx->key); i++) ctx->enckey[i] = ctx->deckey[i] = k[i];
	for (i = 8;--i;) aes_expandEncKey(ctx->deckey, &rcon);
} /* aes256_init */

/* -------------------------------------------------------------------------- */
void aes256_done(aes256_context *ctx)
{
	register uint8_t i;

	for (i = 0; i < sizeof(ctx->key); i++) 
		ctx->key[i] = ctx->enckey[i] = ctx->deckey[i] = 0;
} /* aes256_done */

/* -------------------------------------------------------------------------- */
void aes256_encrypt_ecb(aes256_context *ctx, uint8_t *buf)
{
	uint8_t i, rcon;

	aes_addRoundKey_cpy(buf, ctx->enckey, ctx->key);
	for(i = 1, rcon = 1; i < 14; ++i)
	{
		aes_subBytes(buf);
		aes_shiftRows(buf);
		aes_mixColumns(buf);
		if( i & 1 ) aes_addRoundKey( buf, &ctx->key[16]);
		else aes_expandEncKey(ctx->key, &rcon), aes_addRoundKey(buf, ctx->key);
	}
	aes_subBytes(buf);
	aes_shiftRows(buf);
	aes_expandEncKey(ctx->key, &rcon); 
	aes_addRoundKey(buf, ctx->key);
} /* aes256_encrypt */

/* -------------------------------------------------------------------------- */
void aes256_decrypt_ecb(aes256_context *ctx, uint8_t *buf)
{
	uint8_t i, rcon;

	aes_addRoundKey_cpy(buf, ctx->deckey, ctx->key);
	aes_shiftRows_inv(buf);
	aes_subBytes_inv(buf);

	for (i = 14, rcon = 0x80; --i;)
	{
		if( ( i & 1 ) )           
		{
			aes_expandDecKey(ctx->key, &rcon);
			aes_addRoundKey(buf, &ctx->key[16]);
		}
		else aes_addRoundKey(buf, ctx->key);
		aes_mixColumns_inv(buf);
		aes_shiftRows_inv(buf);
		aes_subBytes_inv(buf);
	}
	aes_addRoundKey( buf, ctx->key); 
} /* aes256_decrypt */

#endif

#ifndef _MD5_H
	#define _MD5_H
	/*md5.h*/
	/* Any 32-bit or wider unsigned integer data type will do */
	#define _CRT_SECURE_NO_WARNINGS
	#include <string.h>
	typedef unsigned int MD5_u32plus;

	typedef struct {
		MD5_u32plus lo, hi;
		MD5_u32plus a, b, c, d;
		unsigned char buffer[64];
		MD5_u32plus block[16];
	} MD5_CTX;

	extern void MD5_Init(MD5_CTX *ctx);
	extern void MD5_Update(MD5_CTX *ctx, void *data, unsigned long size);
	extern void MD5_Final(unsigned char *result, MD5_CTX *ctx);
	/*
		* This is an OpenSSL-compatible implementation of the RSA Data Security, Inc.
		* MD5 Message-Digest Algorithm (RFC 1321).
		*
		* Homepage:
		* http://openwall.info/wiki/people/solar/software/public-domain-source-code/md5
		*
		* Author:
		* Alexander Peslyak, better known as Solar Designer <solar at openwall.com>
		*
		* This software was written by Alexander Peslyak in 2001.  No copyright is
		* claimed, and the software is hereby placed in the public domain.
		* In case this attempt to disclaim copyright and place the software in the
		* public domain is deemed null and void, then the software is
		* Copyright (c) 2001 Alexander Peslyak and it is hereby released to the
		* general public under the following terms:
		*
		* Redistribution and use in source and binary forms, with or without
		* modification, are permitted.
		*
		* There's ABSOLUTELY NO WARRANTY, express or implied.
		*
		* (This is a heavily cut-down "BSD license".)
		*
		* This differs from Colin Plumb's older public domain implementation in that
		* no exactly 32-bit integer data type is required (any 32-bit or wider
		* unsigned integer data type will do), there's no compile-time endianness
		* configuration, and the function prototypes match OpenSSL's.  No code from
		* Colin Plumb's implementation has been reused; this comment merely compares
		* the properties of the two independent implementations.
		*
		* The primary goals of this implementation are portability and ease of use.
		* It is meant to be fast, but not as fast as possible.  Some known
		* optimizations are not included to reduce source code size and avoid
		* compile-time configuration.
		*/
	#define F(x, y, z)			((z) ^ ((x) & ((y) ^ (z))))
	#define G(x, y, z)			((y) ^ ((z) & ((x) ^ (y))))
	#define H(x, y, z)			((x) ^ (y) ^ (z))
	#define I(x, y, z)			((y) ^ ((x) | ~(z)))
	#define STEP(f, a, b, c, d, x, t, s) \
		(a) += f((b), (c), (d)) + (x) + (t); \
		(a) = (((a) << (s)) | (((a) & 0xffffffff) >> (32 - (s)))); \
		(a) += (b);
	#if defined(__i386__) || defined(__x86_64__) || defined(__vax__)
	#define SET(n) \
		(*(MD5_u32plus *)&ptr[(n) * 4])
	#define GET(n) \
		SET(n)
	#else
	#define SET(n) \
		(ctx->block[(n)] = \
		(MD5_u32plus)ptr[(n) * 4] | \
		((MD5_u32plus)ptr[(n) * 4 + 1] << 8) | \
		((MD5_u32plus)ptr[(n) * 4 + 2] << 16) | \
		((MD5_u32plus)ptr[(n) * 4 + 3] << 24))
	#define GET(n) \
		(ctx->block[(n)])
	#endif
	static void *body(MD5_CTX *ctx, void *data, unsigned long size)
	{
		unsigned char *ptr;
		MD5_u32plus a, b, c, d;
		MD5_u32plus saved_a, saved_b, saved_c, saved_d;

		ptr = (unsigned char*)data;

		a = ctx->a;
		b = ctx->b;
		c = ctx->c;
		d = ctx->d;

		do {
			saved_a = a;
			saved_b = b;
			saved_c = c;
			saved_d = d;

	/* Round 1 */
			STEP(F, a, b, c, d, SET(0), 0xd76aa478, 7)
			STEP(F, d, a, b, c, SET(1), 0xe8c7b756, 12)
			STEP(F, c, d, a, b, SET(2), 0x242070db, 17)
			STEP(F, b, c, d, a, SET(3), 0xc1bdceee, 22)
			STEP(F, a, b, c, d, SET(4), 0xf57c0faf, 7)
			STEP(F, d, a, b, c, SET(5), 0x4787c62a, 12)
			STEP(F, c, d, a, b, SET(6), 0xa8304613, 17)
			STEP(F, b, c, d, a, SET(7), 0xfd469501, 22)
			STEP(F, a, b, c, d, SET(8), 0x698098d8, 7)
			STEP(F, d, a, b, c, SET(9), 0x8b44f7af, 12)
			STEP(F, c, d, a, b, SET(10), 0xffff5bb1, 17)
			STEP(F, b, c, d, a, SET(11), 0x895cd7be, 22)
			STEP(F, a, b, c, d, SET(12), 0x6b901122, 7)
			STEP(F, d, a, b, c, SET(13), 0xfd987193, 12)
			STEP(F, c, d, a, b, SET(14), 0xa679438e, 17)
			STEP(F, b, c, d, a, SET(15), 0x49b40821, 22)

	/* Round 2 */
			STEP(G, a, b, c, d, GET(1), 0xf61e2562, 5)
			STEP(G, d, a, b, c, GET(6), 0xc040b340, 9)
			STEP(G, c, d, a, b, GET(11), 0x265e5a51, 14)
			STEP(G, b, c, d, a, GET(0), 0xe9b6c7aa, 20)
			STEP(G, a, b, c, d, GET(5), 0xd62f105d, 5)
			STEP(G, d, a, b, c, GET(10), 0x02441453, 9)
			STEP(G, c, d, a, b, GET(15), 0xd8a1e681, 14)
			STEP(G, b, c, d, a, GET(4), 0xe7d3fbc8, 20)
			STEP(G, a, b, c, d, GET(9), 0x21e1cde6, 5)
			STEP(G, d, a, b, c, GET(14), 0xc33707d6, 9)
			STEP(G, c, d, a, b, GET(3), 0xf4d50d87, 14)
			STEP(G, b, c, d, a, GET(8), 0x455a14ed, 20)
			STEP(G, a, b, c, d, GET(13), 0xa9e3e905, 5)
			STEP(G, d, a, b, c, GET(2), 0xfcefa3f8, 9)
			STEP(G, c, d, a, b, GET(7), 0x676f02d9, 14)
			STEP(G, b, c, d, a, GET(12), 0x8d2a4c8a, 20)

	/* Round 3 */
			STEP(H, a, b, c, d, GET(5), 0xfffa3942, 4)
			STEP(H, d, a, b, c, GET(8), 0x8771f681, 11)
			STEP(H, c, d, a, b, GET(11), 0x6d9d6122, 16)
			STEP(H, b, c, d, a, GET(14), 0xfde5380c, 23)
			STEP(H, a, b, c, d, GET(1), 0xa4beea44, 4)
			STEP(H, d, a, b, c, GET(4), 0x4bdecfa9, 11)
			STEP(H, c, d, a, b, GET(7), 0xf6bb4b60, 16)
			STEP(H, b, c, d, a, GET(10), 0xbebfbc70, 23)
			STEP(H, a, b, c, d, GET(13), 0x289b7ec6, 4)
			STEP(H, d, a, b, c, GET(0), 0xeaa127fa, 11)
			STEP(H, c, d, a, b, GET(3), 0xd4ef3085, 16)
			STEP(H, b, c, d, a, GET(6), 0x04881d05, 23)
			STEP(H, a, b, c, d, GET(9), 0xd9d4d039, 4)
			STEP(H, d, a, b, c, GET(12), 0xe6db99e5, 11)
			STEP(H, c, d, a, b, GET(15), 0x1fa27cf8, 16)
			STEP(H, b, c, d, a, GET(2), 0xc4ac5665, 23)

	/* Round 4 */
			STEP(I, a, b, c, d, GET(0), 0xf4292244, 6)
			STEP(I, d, a, b, c, GET(7), 0x432aff97, 10)
			STEP(I, c, d, a, b, GET(14), 0xab9423a7, 15)
			STEP(I, b, c, d, a, GET(5), 0xfc93a039, 21)
			STEP(I, a, b, c, d, GET(12), 0x655b59c3, 6)
			STEP(I, d, a, b, c, GET(3), 0x8f0ccc92, 10)
			STEP(I, c, d, a, b, GET(10), 0xffeff47d, 15)
			STEP(I, b, c, d, a, GET(1), 0x85845dd1, 21)
			STEP(I, a, b, c, d, GET(8), 0x6fa87e4f, 6)
			STEP(I, d, a, b, c, GET(15), 0xfe2ce6e0, 10)
			STEP(I, c, d, a, b, GET(6), 0xa3014314, 15)
			STEP(I, b, c, d, a, GET(13), 0x4e0811a1, 21)
			STEP(I, a, b, c, d, GET(4), 0xf7537e82, 6)
			STEP(I, d, a, b, c, GET(11), 0xbd3af235, 10)
			STEP(I, c, d, a, b, GET(2), 0x2ad7d2bb, 15)
			STEP(I, b, c, d, a, GET(9), 0xeb86d391, 21)

			a += saved_a;
			b += saved_b;
			c += saved_c;
			d += saved_d;

			ptr += 64;
		} while (size -= 64);

		ctx->a = a;
		ctx->b = b;
		ctx->c = c;
		ctx->d = d;

		return ptr;
	}

	void MD5_Init(MD5_CTX *ctx)
	{
		ctx->a = 0x67452301;
		ctx->b = 0xefcdab89;
		ctx->c = 0x98badcfe;
		ctx->d = 0x10325476;

		ctx->lo = 0;
		ctx->hi = 0;
	}

	void MD5_Update(MD5_CTX *ctx, void *data, unsigned long size)
	{
		MD5_u32plus saved_lo;
		unsigned long used, free;

		saved_lo = ctx->lo;
		if ((ctx->lo = (saved_lo + size) & 0x1fffffff) < saved_lo)
			ctx->hi++;
		ctx->hi += size >> 29;

		used = saved_lo & 0x3f;

		if (used) {
			free = 64 - used;

			if (size < free) {
				memcpy(&ctx->buffer[used], data, size);
				return;
			}

			memcpy(&ctx->buffer[used], data, free);
			data = (unsigned char *)data + free;
			size -= free;
			body(ctx, ctx->buffer, 64);
		}

		if (size >= 64) {
			data = body(ctx, data, size & ~(unsigned long)0x3f);
			size &= 0x3f;
		}

		memcpy(ctx->buffer, data, size);
	}

	void MD5_Final(unsigned char *result, MD5_CTX *ctx)
	{
		unsigned long used, free;

		used = ctx->lo & 0x3f;

		ctx->buffer[used++] = 0x80;

		free = 64 - used;

		if (free < 8) {
			memset(&ctx->buffer[used], 0, free);
			body(ctx, ctx->buffer, 64);
			used = 0;
			free = 64;
		}

		memset(&ctx->buffer[used], 0, free - 8);

		ctx->lo <<= 3;
		ctx->buffer[56] = ctx->lo;
		ctx->buffer[57] = ctx->lo >> 8;
		ctx->buffer[58] = ctx->lo >> 16;
		ctx->buffer[59] = ctx->lo >> 24;
		ctx->buffer[60] = ctx->hi;
		ctx->buffer[61] = ctx->hi >> 8;
		ctx->buffer[62] = ctx->hi >> 16;
		ctx->buffer[63] = ctx->hi >> 24;

		body(ctx, ctx->buffer, 64);

		result[0] = ctx->a;
		result[1] = ctx->a >> 8;
		result[2] = ctx->a >> 16;
		result[3] = ctx->a >> 24;
		result[4] = ctx->b;
		result[5] = ctx->b >> 8;
		result[6] = ctx->b >> 16;
		result[7] = ctx->b >> 24;
		result[8] = ctx->c;
		result[9] = ctx->c >> 8;
		result[10] = ctx->c >> 16;
		result[11] = ctx->c >> 24;
		result[12] = ctx->d;
		result[13] = ctx->d >> 8;
		result[14] = ctx->d >> 16;
		result[15] = ctx->d >> 24;

		memset(ctx, 0, sizeof(*ctx));
	}

#endif

#ifndef MD5_HASH_ENCRYPT_DECRYPT
	#define _CRT_SECURE_NO_WARNINGS
	#include <iostream>
	#define HASH_SIZE 33
	using namespace std;

	int md5Hash(const char account_no[], char md5_hash_account_no[])
	{
		MD5_CTX file_hash;
		MD5_Init(&file_hash);
		char *account_num;
		int acc_no_len = strlen(account_no);
		if(acc_no_len != 11 )
			return -1;
		account_num = (char*)account_no;
		MD5_Update(&file_hash, account_num, strlen(account_num));
		unsigned char result[16];
		MD5_Final(result, &file_hash);
		char md5string[33];
		for(int i=0; i<16; i++)
			sprintf(&md5string[i*2], "%02x", (unsigned int)result[i]);
		strcpy(md5_hash_account_no, md5string);
		return 0;
	}

	int Encrypt(const char account_n[], const char passphrase[]){
		char account_hash[HASH_SIZE];
		//Get Account Name from md5Hash
		char account_name[33] = "12345-12345";
		const char account_no[] = "12345-12345";
		if(md5Hash(account_no, account_name) != 0)
		{
			cout<<"Error: MD5HASH Error"<<endl;
			return false;
		}

		//Open Output File in Append Mode
		FILE* iofile = fopen(account_name, "r+");
		if ( !iofile )
		{
			cout << "Error: Cannot find file"<< account_name << endl;
			return false; 
		}

		//Buffer to hold all file data
		char* buffer;
		size_t result;
		long lSize;
		// obtain file size:
		fseek (iofile , 0 , SEEK_END);
		lSize = ftell (iofile);
		rewind (iofile);

		// allocate memory to contain the whole file:
		long size_of_array = sizeof(char)*(lSize);
		if(size_of_array%16 != 0)
			size_of_array = ((size_of_array/16)+1)*16;
		buffer = (char*) malloc (sizeof(char)*(size_of_array));
		if (buffer == NULL) {fputs ("Memory Error in Encrypt",stderr); exit (2);}

		// copy the file into the buffer:
		result = fread (buffer,1,lSize,iofile);
		for(int i=lSize; i<size_of_array;i++)
			buffer[i]='\0';
		buffer[size_of_array-1]='\0';
		cout<<"LSize, Size_of_Array, Result = "<<lSize<<", "<<size_of_array<<", "<<result<<endl;
		if (ferror(iofile)) {fputs ("Reading Error in Encrypt",stderr); exit (3);}

		//Encrypt
		aes256_context ctx; 
		aes256_init(&ctx, (unsigned char*)passphrase);
		aes256_encrypt_ecb(&ctx, (unsigned char*)buffer);

		//Write back to file
		iofile = freopen(account_name, "w+", iofile);
		result = fwrite (buffer,1,size_of_array,iofile);

		if (ferror(iofile)) {fputs ("Writing Error in Encrypt",stderr); exit (3);}
		free(buffer);

		fclose(iofile);
		return 0;
	}

	int Decrypt(const char account_n[], const char passphrase[]){
		char account_hash[HASH_SIZE];
		//Get Account Name from md5Hash
		char account_name[33] = "12345-12345";
		const char account_no[] = "12345-12345";
		if(md5Hash(account_no, account_name) != 0)
		{
			cout<<"Error: MD5HASH Error"<<endl;
			return false;
		}

		//Open Output File in Append Mode
		FILE* iofile = fopen(account_name, "r+");
		if ( !iofile )
		{
			cout << "Error: Cannot find file"<< account_name << endl;
			return false; 
		}

		//Buffer to hold all file data
		char* buffer;
		size_t result;
		long lSize;
		// obtain file size:
		fseek (iofile , 0 , SEEK_END);
		lSize = ftell (iofile);
		rewind (iofile);

		// allocate memory to contain the whole file:
		long size_of_array = sizeof(char)*(lSize);
		if(size_of_array%16 != 0)
			size_of_array = ((size_of_array/16)+1)*16;
		buffer = (char*) malloc (size_of_array);
		if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

		// copy the file into the buffer:
		result = fread (buffer,1,lSize,iofile);
		if (ferror(iofile)) {fputs ("Reading Error in Decrypt",stderr); exit (3);}

		//Encrypt
		aes256_context ctx; 
		/*aes256_init(&ctx, (uint8_t*)passphrase);
		aes256_encrypt_ecb(&ctx, (uint8_t*)buffer);*/

		aes256_init(&ctx, (unsigned char*)passphrase);
		aes256_decrypt_ecb(&ctx, (unsigned char*)buffer);
		//Write back to file
		lSize = 0;
		for(int i=0; i<size_of_array;i++){
			if(buffer[i]=='\0'||!isascii(buffer[i]))
				buffer[i]='\0';
			else
				lSize++;
		}
		iofile = freopen(account_name, "w+", iofile);
		result = fwrite (buffer,1,lSize,iofile);

		if (ferror(iofile)) {fputs ("Writing Error in Decrypt",stderr); exit (3);}

		free(buffer);
		fclose(iofile);
		return 0;
	}

#endif
