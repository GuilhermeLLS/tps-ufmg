

# Trabalho Prático sobre Testes de Software
Trabalho para a disciplina de Prática e Desenvolvimento de Softwares na UFMG sobre casos reais de testes de software.

**Aluno**: Guilherme Luiz Lara Silva <br/>
**Matrícula**: 2019054633

## Repositório observado: ChakraUI

Os testes desse TP foram retirados do repositório da biblioteca de UI para React chamada [ChakraUI](https://github.com/chakra-ui/chakra-ui). Ela é uma biblioteca open source, criada pelo nigeriano Sage Adebayo e mantido por diversos outros desenvolvedores. Ela foi minha escolha pelo fato de ser algo que uso no dia a dia e possuo certa familiaridade.


## Ferramenta de testes

Para os testes observados abaixo, foram utilizadas as bibliotecas jest e react testing library (que usa o jest internamente). O jest é um biblioteca de propóstito geral para testes em javascript, e o react testing library é uma biblioteca dos mesmos criadores da testing-library, uma biblioteca geral para testes de javascript à nivel de UI. Vale ressaltar que a família testing-library, possui outras "variações", como o vue-testing-library, reason-testing-library, svelte-testing-library, dentre outros. Todos os outros filhos da testing-library são feitos para frameworks javascript, bibliotecas javascript ou linguagens que compilam para javascript (que é o caso do ReasonML).

## Testes observados

### Array Utils

Escolhi esse [teste](https://github.com/chakra-ui/chakra-ui/blob/main/packages/utils/tests/array.test.ts#L115) em específico, pois ele não trata sobre comportamentos de uma UI. Se trata de um teste de uma função "pura", que dado um certo input, ela sempre produzirá o mesmo output. Pure functions são muito comuns em linguagens de paradigmas funcionais, como Elixir, OCaml e Haskell.

```ts
test.each([
  ["base", true],
  ["sm", true],
  ["md", true],
  ["lg", true],
  ["xl", true],
  ["xxl", true],
  ["custom", true],
  ["2xl", true],
  ["0", false],
  ["1", false],
  ["2", false],
  ["3", false],
  ["4", false],
  ["5", false],
])("given %s, returns %s", (given, expected) => {
  expect(isCustomBreakpoint(given)).toBe(expected)
})
```

Neste teste, temos uma matriz 14x2, tal que a primeira coluna é composta por valores que devem ser testados e a segunda coluna é composta por valores booleanos, que são os resultados esperados do teste. O método test.each da biblioteca jest, recebe a matriz por parâmetros e executa o teste a partir dos valores presentes nela. No caso, o teste é para averiguar se tal valor é um "breakpoint". Um "breakpoint" no contexto do ChakraUI representa o nome + valor arbitrário do tamanho da tela. Ou seja, um breakpoint lg pode representar uma tela de 792px de largura e o 2xl uma tela de 2560px de largura. Dessa forma é possível criar estilos responsivos com a biblioteca.

Voltando ao teste, esse teste testa a função `isCustomBreakpoint`, que checa internamente se um valor é um breakpoint ou não. Os nomes de um Breakpoint podem ser qualquer coisa, desde que não sejam números, e é exatamente isso o que a função `isCustomBreakpoint` faz.

```ts
const isCustomBreakpoint = (maybeBreakpoint: string) => Number.isNaN(Number(maybeBreakpoint))
```

Dessa forma, a estrutura do teste é a seguinte:
```ts
test.each(MATRIX)('test description text', (callback_arg1, callback_arg2) => test_assertion)
```

### Avatar Component

Esse [teste](https://github.com/chakra-ui/chakra-ui/blob/main/packages/avatar/tests/avatar.test.tsx#L66) é relacionado ao componente de Avatar. O componente de Avatar renderiza uma imagem de acordo com as iniciais de um nome o qual foi passado para ele ou renderiza uma imagem que foi passada para ele. Ou seja, se passarmos uma image, ele irá renderizar esta imagem e se não passarmos uma imagem e passarmos um nome como, Guilherme Luiz, ele irá renderizar um círculo com as letras GL no centro, sendo o círculo e o centro de cores aleatórias.

```tsx
test("renders an image", async () => {
  mockImage(LOAD_IMAGE)
  const src = "https://bit.ly/dan-abramov"
  const name = "Dan Abramov"
  const { container } = render(<Avatar src={src} name={name} />)

  await waitFor(() => {
    jest.advanceTimersByTime(DELAY)
  })

  const img = container.querySelector("img")
  expect(img).toHaveAttribute("src", src)
  expect(img).toHaveAttribute("alt", name)
})
```

No caso acima, o teste é basicamente uma checagem se o componente de Avatar renderizou uma imagem e se possuí os atributos HTML corretos. É utilizado a função utilitária `render` do react-testing-lib, que renderiza um componente react. As asserssões são checagens da existência de atributos HTML no elemento que foi selecionado e armazenado na variável img. As asserssões esperam que o componente tenha as propriedades src e alt iguais ao valores recebidos via props pelo componente de Avatar.

### Portal Component

Esse [teste](https://github.com/chakra-ui/chakra-ui/blob/main/packages/portal/tests/portal.test.tsx#L48) é relacionado ao componente de Portal. No ponto de vista de uma árvore HTML, um Portal é um nó renderizado fora da hierarquia da árvore HTML do elemento pai. 

Em termos de código, ao escrevermos algo assim::

```html
<html>
    <body>
        <main>
            Content....
            <portal>Portal content unrelated to body content</portal>
        </main>
    </body>
</html>
```
Será renderizado algo assim:

```html
<html>
    <body>
        <main>Content....</main>
    </body>
    <portal>Portal content unrelated to body content</portal>
</html>
```

O teste escolhido, checa exatamente se um portal não é filho do nó o qual ele foi declarado após na hierarquia do JSX.

```jsx
test("should render in a different node", () => {
  render(
    <PortalManager>
      <div data-testid="parent">
        <h1 data-testid="child-1">Foo</h1>
        <Portal>
          <h1 data-testid="child-2">Foo</h1>
        </Portal>
      </div>
    </PortalManager>,
  )

  const parent = screen.getByTestId("parent")

  const child1 = screen.getByTestId("child-1")
  const child2 = screen.getByTestId("child-2")

  expect(parent).toContainElement(child1)
  expect(parent).not.toContainElement(child2)
})
```

Nesse teste, temos uma div, que é pai de um h1 e de um Portal. Também temos que esse Portal, tem um filho que também é um h1. Portanto, se seguirmos o conceito de Portais, mesmo que o Portal parece ser um filho da div, ele deve ser renderizado em outro nó separado da árvore do HTML. Dessaa forma, a melhor forma de checarmos isso, é verificar se a div pai **não** possui os filhos do portal (o h1 com test-id igual à child-2).