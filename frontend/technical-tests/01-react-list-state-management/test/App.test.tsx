import React from 'react'
import { describe, test, expect } from 'vitest'
import { render, screen } from '@testing-library/react'
import userEvent from '@testing-library/user-event'
import App from '../src/App'

describe('<App />', () => {
    // test('should work', () => {
    //     render(<App />)
    //     screen.debug()

    // })

    // Test End to End
    test('should add a items and remoeve them', async () => {
        const user = userEvent.setup() // to simulate user events

        render(<App />) // render the component

        // Search input
        const input = screen.getByRole('textbox')
        expect(input).toBeDefined()

        // Search form
        const form = screen.getByRole('form')
        expect(form).toBeDefined()

        const button = form.querySelector('button')
        expect(button).toBeDefined()

        // Write a new item
        const randomText = crypto.randomUUID()

        await user.type(input, randomText)
        await user.click(button!)

        // Verify that the item was added
        const list = screen.getByRole('list')
        expect(list).toBeDefined()
        expect(list.children.length).toBe(1)

        // Verify that can remove items
        const item = screen.getByText(randomText)
        const removeButton = item.querySelector('button')
        expect(removeButton).toBeDefined()

        await user.click(removeButton!)

        const noResults = screen.queryByText('No items available')
        expect(noResults).toBeDefined()

    })
})