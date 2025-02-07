/*
 * Copyright (C) 2021-2022 Twilight-Dream
 *
 * 本文件是 TDOM-EncryptOrDecryptFile-Reborn 的一部分。
 *
 * TDOM-EncryptOrDecryptFile-Reborn 是自由软件：你可以再分发之和/或依照由自由软件基金会发布的 GNU 通用公共许可证修改之，无论是版本 3 许可证，还是（按你的决定）任何以后版都可以。
 *
 * 发布 TDOM-EncryptOrDecryptFile-Reborn 是希望它能有用，但是并无保障;甚至连可销售和符合某个特定的目的都不保证。请参看 GNU 通用公共许可证，了解详情。
 * 你应该随程序获得一份 GNU 通用公共许可证的复本。如果没有，请看 <https://www.gnu.org/licenses/>。
 */
 
 /*
 * Copyright (C) 2021-2022 Twilight-Dream
 *
 * This document is part of TDOM-EncryptOrDecryptFile-Reborn.
 *
 * TDOM-EncryptOrDecryptFile-Reborn is free software: you may redistribute it and/or modify it under the GNU General Public License as published by the Free Software Foundation, either under the Version 3 license, or (at your discretion) any later version.
 *
 * TDOM-EncryptOrDecryptFile-Reborn is released in the hope that it will be useful, but there are no guarantees; not even that it will be marketable and fit a particular purpose. Please see the GNU General Public License for details.
 * You should get a copy of the GNU General Public License with your program. If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "./IsFor_EODF_Reborn.hpp"
#include "./UnitTester.hpp"

auto main(int argument_cout, char* argument_vector[]) -> int
{
	std::cout.tie(0)->sync_with_stdio(false);

	UnitTester::Test_BuildingKeyStream();

	UnitTester::Test_ByteSubstitutionBoxToolkit();

	//74 68 61 74 73 20 6D 79 20 6B 75 6E 67 20 66 75
	//21 40 23 24 25 5E 26 2A 28 29 30 38 34 36 32 35
	//std::vector<std::uint8_t> Keys = UtilTools::DataFormating::ASCII_Hexadecmial::hexadecimalString2ByteArray(std::string("21402324255E262A2829303834363235"));
	//auto SubsitiutionBoxPair = CustomSecurity::DataObfuscator::SubsitiutionBox::GeneratorAlgorithm(Keys);
	//auto SubsitiutionBoxPair = CustomSecurity::DataObfuscator::SubsitiutionBox::GeneratorAlgorithm2();

	//UnitTester::Test_CustomDataObfuscator();
	std::cout << std::endl;

	/*

	CommonSecurity::RNG_ISAAC::isaac<8> ISAAC(1597346285);
	CommonSecurity::RNG_ISAAC::isaac64<8> ISAAC64(1597346285);

	std::vector<std::uint32_t> random_32bit_numbers;
	std::vector<std::uint64_t> random_64bit_numbers;

	for(std::size_t round = 1024; round > 0; --round)
	{
		random_32bit_numbers.push_back(ISAAC());
	}

	for(std::size_t round = 1024; round > 0; --round)
	{
		random_64bit_numbers.push_back(ISAAC64());
	}

	std::cout << std::endl;

	*/

	/*

	CommonSecurity::RNG_SimpleImplementation::GNU_C_LibraryGenerator PRNG_GNU_C_Library(1);

	std::vector<char> RNG_bytes_state
	{
		8, -72, 13, -54, -55, 85, 43, -127,
		66, -49, 1, 13, -111, 7, 46, 22,
		59, -21, 9, -88, 47, 58, -44, 11,
		-33, 64, 3, 48, -62, 5, -2, 0, 99
	};

	std::vector<char> RNG_bytes_state2
	{
		-34, -101, 3, 48, -62, 5, -44, 0, 99,
		66, 59, 2, 13, 121, 7, 46, 66,
		19, 56, 13, -54, -55, 85, 43, -127,
		59, -21, 42, -88, 47, 58, -44, 11,
	};

	unsigned int seed_number = 1;

	auto PRNG_GNU_C_LibraryStateArgument = std::pair<unsigned int, std::span<const char>>(seed_number, RNG_bytes_state);
	auto PRNG_GNU_C_LibraryStateArgument2 = std::pair<unsigned int, std::span<const char>>(seed_number, RNG_bytes_state2);

	PRNG_GNU_C_LibraryStateArgument.first = PRNG_GNU_C_Library.easy_compute_number(seed_number);
	auto PRNG_GNU_C_LibraryStatePairValue = PRNG_GNU_C_Library.initial_state(PRNG_GNU_C_LibraryStateArgument);
	if(PRNG_GNU_C_LibraryStatePairValue.has_value())
	{
		auto& PRNG_GNU_C_LibraryStatePair = PRNG_GNU_C_LibraryStatePairValue.value();
		PRNG_GNU_C_Library.update_state(PRNG_GNU_C_LibraryStateArgument2, PRNG_GNU_C_LibraryStatePair.second);
		PRNG_GNU_C_Library.change_state(PRNG_GNU_C_LibraryStatePair.second);
	}

	std::vector<int> RNG_test_random_numbers;

	for(std::size_t count = 128; count > 0; --count)
	{
		auto&& random_number = PRNG_GNU_C_Library();
		RNG_test_random_numbers.push_back(random_number);
	}

	*/

	//MemoryTrackUsageInfo::get_instance().SetIsTracked(true);

	#ifdef _WIN32
	std::system("pause");
	#else
    std::system("read -p Press\\ Any\\ Key\\ To\\ Continue");
	#endif

	return 0;
}