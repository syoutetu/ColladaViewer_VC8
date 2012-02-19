
#pragma once

#if !defined ___DomNodeReader_h___
#define ___DomNodeReader_h___



// DOM�m�[�h��ǂݍ��ރC���^�[�t�F�[�X
class DomNodeReader
{
public:

	// DOM�m�[�h��ǂݍ���
	virtual void ReadNode(const DOMNode* node) = 0;

	// �v�f������ȏ�Ԃɂ���(�K���K�v�ȑ������ǂݍ��܂ꂽ)���Ƃ��m�F����
	// �G���[������ꍇ��message�ɒǉ�����
	virtual bool ValidElements(std::wstring& message) const = 0;	

protected:

	DomNodeReader()	{}
	virtual ~DomNodeReader()	{}

};



// ====================================
// �e���v���[�g�֐�
// ====================================

// size()�ŃT�C�Y�A[]��DomNodeReader*���擾�ł���R���e�i����ValidElements()����������
template<typename _Cnt>	
inline void ValidElementsInContainer(_Cnt& cnt, std::wstring& message)
{
	unsigned int size = (unsigned int)cnt.size();
	for( unsigned int i = 0; i < size; i++ ) { cnt[i]->ValidElements( message ); }
}


#endif	//___DomNodeReader_h___