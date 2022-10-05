#ifndef GAP_BUFFER_HPP
#define GAP_BUFFER_HPP

class gapBuffer
{
  public:
    gapBuffer();
    gapBuffer(int s);
    ~gapBuffer();

    void insert(char ch);
    int getSize() const;
    void display() const;
    void right();
    void left();
private:
    char* m_txt;
    char* m_left;
    char* m_right;
    int m_size;

    int m_growthFactor;
    void growth();
};

gapBuffer::gapBuffer()
{
    m_size = 7;
    m_growthFactor = 2;
    m_txt = new char[m_size + 1];
    for (int i = 0; i < m_size; ++i) { m_txt[i] = '_'; }
    m_txt[m_size] = '\0';
    m_left = m_txt;
    m_right = (m_txt + m_size);
}

gapBuffer::gapBuffer(int s)
{
    m_size = s;
    m_growthFactor = 2;
    m_txt = new char[m_size + 1];
    for (int i = 0; i < m_size; ++i) { m_txt[i] = '_'; }
    m_txt[m_size] = '\0';
    m_left = m_txt;
    m_right = (m_txt + m_size);
}

gapBuffer::~gapBuffer()
{
  delete m_txt;
}

void gapBuffer::growth()
{
  int newSize = m_size * m_growthFactor;
  char* tmp = new char[newSize + 1];
  for (int i = 0; i < newSize; ++i) { tmp[i] = '_'; }
  tmp[newSize] = '\0';
  int end = newSize - 1;
  int st = 0;
  while (m_txt[st] != '_' && st < m_size)
  {
    tmp[st] = m_txt[st];
    st++;
  }
  if (st <= m_size)
  {
    int j = m_size;
    while ((m_txt + j) != m_left && m_txt[j] != '_' && end >= 0)
    {
      tmp[end] = m_txt[j];
      end--;
      j--;
    }
  }
  delete m_txt;
  m_txt = tmp;
  m_size = newSize;
  m_left = (m_txt + st);
  m_right = (m_txt + end);
}

void gapBuffer::insert(char ch)
{
  *m_left = ch;
  if (m_left == m_right) { growth(); }
  m_left++;
}

void gapBuffer::left()
{
  if(*(m_left - 1) != '\0')
  {
    *m_right = *(m_left - 1);
    *(m_left - 1) = '_';
    m_left--;
    m_right--;
  }
}

void gapBuffer::right()
{
  if (*(m_right + 1) != '\0')
  {
    *m_left = *(m_right + 1);
    *(m_right + 1) = '_';
    m_right++;
    m_left++;
  }
}

void gapBuffer::display() const
{
    int i = 0;
    while (*(m_txt + i)) 
    {
      if(*(m_txt + i) != '_') { std::cout << *(m_txt + i) << " "; }
      i++;
    }
    std::cout << std::endl;
}

int gapBuffer::getSize() const
{
  return m_size;
}

#endif // GAP_BUFFER_HPP 
