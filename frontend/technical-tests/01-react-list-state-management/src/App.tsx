import { Item } from "./components/Item"
import "./App.css"
import { useItems } from "./hooks/useItems"
import { useSEO } from "./hooks/useSEO"

export type ItemId = `${string}-${string}-${string}-${string}-${string}`
export interface Item {
  id: ItemId
  timestamp: number
  text: string
}

function App() {
  const { items, addItem, removeItem } = useItems()

  useSEO({
    title: `[${items.length}] Gestión de Lista - React App`,
    description: "Añadir y eliminar elementos de una lista",
  })

  const handleSubmit = (event: React.FormEvent<HTMLFormElement>) => {
    event.preventDefault()

    const { elements } = event.currentTarget

    const input = elements.namedItem("item")
    const isInput = input instanceof HTMLInputElement
    if (!isInput || input == null) return

    addItem(input.value)

    input.value = ""
  }

  const createHandleRemoveItem = (id: ItemId) => () => {
    removeItem(id)
  }

  return (
    <main>
      <aside>
        <div className="header-section">
          <h1>Gestión de Lista</h1>
          <h2>Añade y elimina elementos de forma sencilla</h2>
        </div>

        <form onSubmit={handleSubmit} aria-label="Añadir elementos a la lista">
          <label htmlFor="item-input">Nuevo elemento</label>
          <input id="item-input" name="item" required type="text" placeholder="Escribe algo... 🎮" autoComplete="off" />
          <button type="submit">
            <span>✨</span> Añadir a la lista
          </button>
        </form>
      </aside>

      <section>
        <h2>
          Lista de elementos
          {items.length > 0 && <span className="item-count">{items.length}</span>}
        </h2>

        {items.length === 0 ? (
          <div className="empty-state">
            <div className="empty-state-icon">📝</div>
            <strong>No hay elementos todavía</strong>
            <p>Añade tu primer elemento usando el formulario</p>
          </div>
        ) : (
          <ul>
            {items.map((item) => {
              return <Item
                {...item}
                handleClick={createHandleRemoveItem(item.id)}
                key={item.id} />
            })}
          </ul>
        )}
      </section>
    </main>
  )
}

export default App
