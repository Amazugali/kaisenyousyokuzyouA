#ifdef _MSC_VER 

// �s�v�Ȍx���̗}��
#pragma warning( disable : 4786 ) // �u�f�o�b�O�����ł̎��ʎq�؎̂āv

// for�X�R�[�v��ANSI����
#ifndef for
#define for if(0);else for
#endif	// for

#endif	// _MSC_VER

#include	<string>
#include	<iostream>
#include	<map>
using namespace std;


// Shift_JIS�ɂ�����S�p�����̂P�o�C�g�ڂ��H
inline bool is_sjis_mb_lead(unsigned char c) {
	if ( c>=0x81 && c<= 0x9F )
		return	true;
	if ( c>=0xE0 && c<= 0xFC )
		return	true;
	return	false;
}


void	main(int argc, char* argv[]) {

	// < �S�̂�1.0�Ƃ����ꍇ�̎��Ԏ���̈ʒu, <�b��, ����> >
	multimap<float, pair<int, string> >	m;

	// �e�b�҂̃g�[�N�𕶎��P�ʂɃo������multimap�Ɋi�[
	for ( int i=1 ; i<argc ; ++i ) {
		const string s = argv[i];
		const int speaker = i-1;

		int	n = 0;
		while ( n < s.size() ) {
			int len = is_sjis_mb_lead(s[n]) ? 2 : 1;
			m.insert( pair<float, pair<int, string> >( 
				1.0f / s.size() * (n + len/2.0f),	// ���Ԏ���̈ʒu
				pair<int, string>(speaker, s.substr(n, len)) 	// �b�҂ƕ���
				));
			n += len;
		}
	}

	// multimap�ւ͏��������Ɋi�[�����B
	// ���Ԏ��ɉ����čč\�� �� �b�Ґ؂�ւ��X�N���v�g�}��
	
	int	last_speaker = -1; // �Ō�̘b�ҁB�����l��A���w�肷�閳�ʂ��Ȃ�����
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
