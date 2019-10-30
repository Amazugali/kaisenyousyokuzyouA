#ifdef _MSC_VER 

// 不要な警告の抑制
#pragma warning( disable : 4786 ) // 「デバッグ情報内での識別子切捨て」

// forスコープのANSI準拠
#ifndef for
#define for if(0);else for
#endif	// for

#endif	// _MSC_VER

#include	<string>
#include	<iostream>
#include	<map>
using namespace std;


// Shift_JISにおける全角文字の１バイト目か？
inline bool is_sjis_mb_lead(unsigned char c) {
	if ( c>=0x81 && c<= 0x9F )
		return	true;
	if ( c>=0xE0 && c<= 0xFC )
		return	true;
	return	false;
}


void	main(int argc, char* argv[]) {

	// < 全体を1.0とした場合の時間軸上の位置, <話者, 文字> >
	multimap<float, pair<int, string> >	m;

	// 各話者のトークを文字単位にバラしてmultimapに格納
	for ( int i=1 ; i<argc ; ++i ) {
		const string s = argv[i];
		const int speaker = i-1;

		int	n = 0;
		while ( n < s.size() ) {
			int len = is_sjis_mb_lead(s[n]) ? 2 : 1;
			m.insert( pair<float, pair<int, string> >( 
				1.0f / s.size() * (n + len/2.0f),	// 時間軸上の位置
				pair<int, string>(speaker, s.substr(n, len)) 	// 話者と文字
				));
			n += len;
		}
	}

	// multimapへは小さい順に格納される。
	// 時間軸に沿って再構成 ＆ 話者切り替えスクリプト挿入
	
	int	last_speaker = -1; // 最後の話者。同じ人を連続指定する無駄を省くため
	for ( multimap<float, pair<int, string> >::const_iterator i = m.begin() ; i != m.end() ; ++i ) {
		const int	speaker = i->second.first;
		if ( speaker != last_speaker )
			if ( speaker < 2 )
				cout << "\\" << speaker;	// \0, \1
			else
				cout << "\\p[" << speaker << "]";	// \p[n]
		cout << i->second.second;
		//cout << "\t" << i->first << endl;
		last_speaker = speaker;
	}
}
