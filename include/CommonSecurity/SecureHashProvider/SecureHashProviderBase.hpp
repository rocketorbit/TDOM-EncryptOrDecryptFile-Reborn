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
 * This file is part of TDOM-EncryptOrDecryptFile-Reborn.
 *
 * TDOM-EncryptOrDecryptFile-Reborn is free software: you may redistribute it and/or modify it under the GNU General Public License as published by the Free Software Foundation, either under the Version 3 license, or (at your discretion) any later version.
 *
 * TDOM-EncryptOrDecryptFile-Reborn is released in the hope that it will be useful, but there are no guarantees; not even that it will be marketable and fit a particular purpose. Please see the GNU General Public License for details.
 * You should get a copy of the GNU General Public License with your program. If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

namespace CommonSecurity
{
	namespace HashProviderBaseTools
	{
		template <typename Type, size_t N>
		struct stream_width_fixer
		{
			stream_width_fixer( Type value ) : _value( value ) {}
			Type _value;
		};

		template <typename Type, size_t N>
		std::ostream& operator<<( std::ostream& os, const stream_width_fixer<Type, N>& swf )
		{
			return os << std::setw( N ) << swf._value;
		}

		inline std::string Bytes2HexadecimalString( std::span<std::byte> in )
		{
			constexpr static std::array<char, 16> transArray{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

			std::string out;
			out.resize( in.size() * 2 );
			std::byte highMask{ 0xF0 };
			std::byte lowMask{ 0x0F };

			for ( size_t input_index = 0, output_index = 0; input_index < in.size(); ++input_index, output_index += 2 )
			{
				out[ output_index ] = transArray[ static_cast<size_t>( ( in[ input_index ] & highMask ) >> 4 ) ];
				out[ output_index + 1 ] = transArray[ static_cast<size_t>( ( in[ input_index ] & lowMask ) ) ];
			}
			return out;
		}

		// Accumulate data and call the transformation function for full blocks.
		template <typename Type, typename TF>
		requires std::is_invocable_r_v<void, TF, std::uint8_t*, std::size_t>
		inline void absorb_bytes( const uint8_t* data, std::size_t data_size, std::size_t block_size, std::size_t block_size_check, CommonSecurity::OneByte* _BufferMessageMemory, std::size_t& position, Type& _total, TF transform_function )
		{
			if ( position && position + data_size >= block_size_check )
			{
				std::memcpy( _BufferMessageMemory + position, data, block_size - position );
				transform_function( _BufferMessageMemory, 1 );
				data_size -= block_size - position;
				data += block_size - position;
				_total += block_size * 8;
				position = 0;
			}
			if ( data_size >= block_size_check )
			{
				std::size_t blocks = ( data_size + block_size - block_size_check ) / block_size;
				std::size_t bytes = blocks * block_size;
				transform_function( data, blocks );
				data_size -= bytes;
				data += bytes;
				_total += ( bytes )*8;
			}
			std::memcpy( _BufferMessageMemory + position, data, data_size );
			position += data_size;
		}

		// Clear memory, suppressing compiler optimizations.
		inline void zero_memory( void* variable, std::size_t size )
		{
			#if 0

			volatile OneByte* data_pointer = static_cast<volatile OneByte*>( variable );
			while ( size-- )
			{
				*data_pointer++ = 0;
			}

			#else

			OneByte* data_pointer = static_cast<OneByte*>( variable );

			std::memset(data_pointer, 0, size);

			#endif
		}

		// Clear memory occupied by an array, suppressing compiler optimizations.
		template <typename Type, size_t N>
		inline void zero_memory( std::array<Type, N>& array_data )
		{
			zero_memory( array_data.data(), array_data.size() * sizeof( Type ) );
		}

		// Clear memory occupied by std::string
		inline void zero_memory( std::string& string_data )
		{
			if ( !string_data.empty() )
				zero_memory( &string_data[ 0 ], string_data.size() );
		}
	}  // namespace HashProviderBaseTools

	namespace HashProviderBaseTools::HashSize
	{
		// Validate that variable hash is within the list of allowed sizes
		inline void validate( std::size_t HashSize, std::initializer_list<std::size_t> initializer_list )
		{
			if ( !HashSize )
			{
				throw std::invalid_argument( std::string( "Hash size can't be zero." ) );
			}

			if ( std::find( initializer_list.begin(), initializer_list.end(), HashSize ) )
			{
				return;
			}

			throw std::runtime_error( "Invalid hash size." );
		}

		// Validate variable hash size up to max bits
		inline void validate( size_t HashSize, size_t max_hash_size )
		{
			if ( !HashSize )
			{
				throw std::invalid_argument( std::string( "Hash size can't be zero." ) );
			}

			if ( HashSize % 8 )
			{
				throw std::runtime_error( "Non-byte hash sizes are not supported." );
			}

			if ( HashSize > max_hash_size )
			{
				throw std::runtime_error( "Invalid hash size." );
			}
		}
	}  // namespace HashProviderBaseTools::HashSize

	namespace HashProviderBaseTools::Traits
	{
		//Is extendable-output function
		template <typename Type>
		struct is_Extendable_OF
		{
			static const bool value = Type::is_Extendable_OF;
		};

		template <typename Type>
		inline constexpr bool is_Extendable_OF_v = is_Extendable_OF<Type>::value;

		//Is byte function
		template <typename Type>
		struct is_byte
		{
			static const bool value = std::is_same_v<Type, char>::value || std::is_same_v<Type, signed char>::value ||
			#if ( defined( _HAS_STD_BYTE ) && _HAS_STD_BYTE ) || ( defined( __cpp_lib_byte ) && __cpp_lib_byte >= 201603 )
				std::is_same_v<Type, std::byte>::value ||
			#endif
				std::is_same_v<Type, unsigned char>::value || std::is_same_v<Type, OneByte>::value;
		};

		template <typename Type>
		inline constexpr bool is_byte_v = is_byte<Type>::value;
	}  // namespace HashProviderBaseTools::Traits

}
