import { useState } from 'react'
import './App.css'

interface Item {
  id: `${string}-${string}-${string}-${string}-${string}`;
  timestamp: number;
  text: string;
}

const INITIAL_ITEMS = [
  {
    id: crypto.randomUUID(),
    timestamp: Date.now(),
    text: 'VideoGames 🎮'
  },
  {
    id: crypto.randomUUID(),
    timestamp: Date.now(),
    text: 'Music 🎵'
  },
  {
    id: crypto.randomUUID(),
    timestamp: Date.now(),
    text: 'Podcasts 🎙️'
  }
]

function App() {
  const [items, setItems] = useState(INITIAL_ITEMS);

  const handleSubmit = (event: React.FormEvent<HTMLFormElement>) => {
    event.preventDefault();

    const { elements } = event.currentTarget

    const input = elements.namedItem('item')
    const isInput = input instanceof HTMLInputElement;
    if (!isInput || input == null) return;

    const newItem: Item = {
      id: crypto.randomUUID(),
      timestamp: Date.now(),
      text: input.value
    }

    setItems((prevItems) => {
      return [...prevItems, newItem];
    });

    input.value = '';
  }

  return (
    <main>
      <aside>
        <h1>React List State Management - Technical Test</h1>
        <h2>Add and Remove Items</h2>

        <form onSubmit={handleSubmit}>
          <label>
            New Item:
            <input 
              name='item'
              required
              type='text'
              placeholder='VideoGames 🎮'
            />
          </label>
          <button type='submit'>Añadir elemento a la lista</button>
        </form>
      </aside>

      <section>
        <h2>Item List</h2>
        <ul>
          {/* Here go the list items */}
          {
            items.map((item) => {
              return (
                <li key={item.id}>
                  {item.text}
                </li>
              )
            })
          }
        </ul>
      </section>
    </main>
  )
}

export default App
